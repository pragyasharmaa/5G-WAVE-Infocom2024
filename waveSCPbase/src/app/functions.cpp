/*
 * Base development module for the WAVE/OAI integration side-car proxy
 *
 * !file functions.cpp
 * \brief
 * \author: Tolga Atalay
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
 */

#include "functions.hpp"

std::unordered_map<std::string, std::string> AttesterIP_To_AttestationHash;
std::unordered_map<std::string, std::string> RequesterIP_To_AttestationHash;
std::unordered_map<std::string, std::string> RequesterIP_To_RequesterHash;
//std::unordered_multimap<std::string, std::string> RequesterIP_To_Hashes;

void WAVEfunctions::send_custom_curl(
        std::string& uri, 
        std::string& message, 
        std::string& response) 
{

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    struct curl_slist *slist1;
    slist1 = NULL;
    slist1 = curl_slist_append(slist1, "Content-Type: application/json");

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 500L);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    response = readBuffer;
    //spdlog::info("Readbuffer is {}", readBuffer);

}

// to check if remote WAVE SCP is active yet
int WAVEfunctions::checkRemoteSCPStatus(
        std::string& authorizerIP) 
{
    int tries = 0;
    std::string curl_request, uri, response(100, ' ');
#if INFO_IS_ON
    spdlog::info("Sending test request to remote SCP");
#endif
    
    // send to WAVE SCP of authorizer VNF
    uri = "http://" + authorizerIP + ":10095";
    curl_request = "test";

    do {
        //response = ' ';
        send_custom_curl(uri, curl_request, response);
#if INFO_IS_ON
        spdlog::info("Response returned is {}", response);
#endif
        tries++;
#if INFO_IS_ON
        spdlog::info("Number of tries is {}", tries);
#endif
        sleep(5);
    } while (response!="Default done" && tries<=20);

    if(response=="Default done") {
        return 1;
    }
    else {
        return 0;    
    }
}

 /*
  * function call when route in http request is /oai/discoverdata
  */
void WAVEfunctions::sendHashForAttestation(
        std::string& authorizerIP) 
{
    std::string curl_request, uri, response(100, ' '), hash;
    std::ifstream hashfile;
    hashfile.open("hash-ent.txt");
    hashfile >> hash;
    hashfile.close();
#if INFO_IS_ON
    spdlog::info("WAVE hash to be sent is {} ", hash);
#endif
    
    // send to WAVE SCP of authorizer VNF
    uri = "http://" + authorizerIP + ":10095/wave/authreq";
    curl_request = hash;
    
    send_custom_curl(uri, curl_request, response);
}

void WAVEfunctions::createWAVEAttestation (
        std::string& requesterHash, 
        const std::string& requesterIP, 
        std::string& rsp) 
{
#if INFO_IS_ON
    spdlog::info("==========Requester Hash Received: {}", requesterHash);
    spdlog::info("==========Requester IP: {}", requesterIP);
#endif
#if DEBUG_IS_ON
    spdlog::debug("Running Att script....");
#endif

    std::string commandStr = "/root/waveSCP/createAtt.sh " + requesterHash;
    const char* command = commandStr.c_str();
    system(command);

#if DEBUG_IS_ON
    spdlog::debug("Attestation Created");
#endif
    rsp = "yes";
    
    std::string attestationHash;
    std::ifstream attHashFile;
    attHashFile.open("hash-att.txt");
    attHashFile >> attestationHash;
    attHashFile.close();
    RequesterIP_To_RequesterHash.insert(std::make_pair(requesterIP, requesterHash)); 
    RequesterIP_To_AttestationHash.insert(std::make_pair(requesterIP, attestationHash)); 
#if DEBUG_IS_ON
    spdlog::debug("==========Requester IP {} mapped to requester hash {} and attestation hash {}", requesterIP, requesterHash, attestationHash);
#endif

}

void WAVEfunctions::sendAuthAck(
        const std::string& requesterIP, 
        std::string& rsp) 
{
    std::string curl_request, uri, response(100, ' ');
    std::string attestationHash;
    std::ifstream attHashFile;
    attHashFile.open("hash-att.txt");
    attHashFile >> attestationHash;
    attHashFile.close();

#if INFO_IS_ON
    spdlog::info("WAVE hash attestation to be sent: {}", attestationHash);
#endif
    
    curl_request = attestationHash;
    uri = "http://" + requesterIP + ":10095/wave/authack";
    send_custom_curl(uri, curl_request, response);

}

void WAVEfunctions::receiveAuthAck(
        const std::string& authorizerIP, 
        std::string& attestationHash) 
{
    AttesterIP_To_AttestationHash.insert(std::make_pair(authorizerIP, attestationHash)); 
    //for (auto& t : AttesterIP_To_AttestationHash) std::cout << t.first << " " << t.second << "\n";
#if DEBUG_IS_ON
    spdlog::debug("==========Authorizer IP {} mapped to attestation hash {}", authorizerIP, attestationHash);
#endif

}


void WAVEfunctions::verifyWAVEAttestation(
        const std::string& requesterIP, 
        std::string& rsp) 
{

    std::unordered_map<std::string, std::string>::iterator it_1 = RequesterIP_To_RequesterHash.find(requesterIP);
    std::unordered_map<std::string, std::string>::iterator it_2 = RequesterIP_To_AttestationHash.find(requesterIP);

    std::string  requesterHash, attestationHash;

    if (it_1 == RequesterIP_To_RequesterHash.end()) {
#if DEBUG_IS_ON
        spdlog::debug("Mapping failed. Requester IP not found in authorized users list");
#endif
    }
    else {
        if (it_2 == RequesterIP_To_AttestationHash.end()) {
#if DEBUG_IS_ON
            spdlog::debug("Mapping failed. Couldn't find attestation provided to requester IP");
#endif
        }
        else {
            requesterHash = it_1->second;
            attestationHash = it_2->second;
        }
    }
#if INFO_IS_ON
    spdlog::info("==========Requester IP : {}", requesterIP);
#endif
#if DEBUG_IS_ON
    spdlog::debug("==========Attestation Hash : {}", attestationHash);
    spdlog::debug("==========Requester Hash : {}", requesterHash);
    spdlog::debug("Running verification script....");
#endif

    std::string commandStr = "/root/waveSCP/verifyAtt.sh " + attestationHash + " " + requesterHash;
    const char* command = commandStr.c_str();
    system(command);

    std::ifstream logfile;
    std::string verificationLog;
    logfile.open("logVerification.txt");
    logfile >> verificationLog;
    logfile.close();
#if DEBUG_IS_ON
    spdlog::debug("=========Verification log is: {}", verificationLog);
#endif

    if (verificationLog.compare("1") == 0) {
#if DEBUG_IS_ON
        spdlog::debug("Attestation verified. Service request granted");
#endif
        rsp = "1";
    }
    else {
#if DEBUG_IS_ON
        spdlog::debug("Attestation not verified. Service request denied");
#endif
        rsp = "0";
    }

}

/*void WAVEfunctions::requestService(std::string& sourceIP, std::string& targetIP) {
    std::string entHash, attestationHash, curl_request, uri, response(100, ' ');
    std::ifstream hashfile;
    hashfile.open("hash-ent.txt");
    hashfile >> entHash;
    hashfile.close();
    
    std::unordered_map<std::string, std::string>::iterator it = IpToAttMap.find(targetIP);
    if (it == IpToAttMap.end()) {
        spdlog::info("Mapping failed. Att hash not found");
    }
    else {
        attestationHash = it->second;
    }
    curl_request = entHash + "&" + attestationHash;
    //uri = "http://" + targetIP + ":10096/wave/checkauth";
    uri = "http://" + targetIP + ":10096/wave/checkauth";
    
    send_custom_curl(uri, curl_request, response);
}*/


/*void WAVEfunctions::createWAVEProof(std::string& authorizerHash, std::string& permHash) {
    spdlog::info("==========Attester Hash Received: {}", authorizerHash);
    spdlog::info("==========Permissions Hash Received: {}", permHash);
    spdlog::debug("Running Proof creation script....");
    
    std::string commandStr = "/root/waveSCP/createProof.sh " + authorizerHash + " " + permHash;
    const char* command = commandStr.c_str();
    system(command);
    
    spdlog::debug("Proof created");
}*/

/*void WAVEfunctions::verifyWAVEProof(std::string& hashRequester) {
    std::string hashAttester;
    std::ifstream hashfile;
    hashfile.open("hash-ent.txt");
    hashfile >> hashAttester;
    hashfile.close();
    std::string filename = "proof-Requester-" + hashRequester + "Attester-" + hashAttester + ".pem";
}*/

/*void WAVEfunctions::sendRqstToGetHashes(std::string& sourceIP, std::string& targetIP) {
    std::string curl_request, uri, response(100, ' ');
    uri = "http://" + targetIP + ":10096/wave/sendauthack";
    //uri = "http://" + targetIP + ":10095/wave/sendauthack";
    curl_request = targetIP + "&" + sourceIP;
    send_custom_curl(uri, curl_request, response);
}*/

/*void WAVEfunctions::sendHashesForProof(std::string& sourceIP, std::string& targetIP) {
    std::string curl_request, uri, response(100, ' '), entHash, hashPerm, attestationHash;
    std::ifstream entHashFile, hashfilePerm, attHashFile;
    entHashFile.open("hash-ent.txt");
    entHashFile >> entHash;
    entHashFile.close();
    hashfilePerm.open("hash-permissions.txt");
    hashfilePerm >> hashPerm;
    hashfilePerm.close();
    attHashFile.open("hash-att.txt");
    attHashFile >> attestationHash;
    attHashFile.close();

    spdlog::info("WAVE hash ent to be sent: {}", entHash);
    spdlog::info("WAVE hash permissions to be sent: {}", hashPerm);
    spdlog::info("WAVE hash attestation to be sent: {}", attestationHash);
    curl_request = entHash + "&" + hashPerm + "&" + attestationHash + "&" + sourceIP;

    uri = "http://" + targetIP + ":10096/wave/recauthack";
    //uri = "http://" + targetIP + ":10095/wave/recauthack";
    send_custom_curl(uri, curl_request, response);

}*/

