/*
 * Base development module for the WAVE/OAI integration side-car proxy
 *
 * ! file handlers.cpp
 *  \brief
 * \author: Tolga Omer Atalay
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/


#include "handlers.hpp"
#include "functions.hpp"

WAVEfunctions* wf_inst = nullptr;

void WAVEHandlers::send_discovery_auth_rqst (
			const std::string& request_main, 
            std::string& rsp, 
			int& http_code, 
            const uint8_t http_version) 
{
		
#if INFO_IS_ON
	spdlog::info("Sending request authorization to remote WAVE SCP");
#endif

    std::vector<std::string> kvpairs;
    boost::split(kvpairs, request_main, boost::is_any_of("&"), boost::token_compress_on);
        
#if INFO_IS_ON
	spdlog::info("=============Requester Entity: {}", kvpairs[0]);
	spdlog::info("=============Requester IP: {}", kvpairs[1]);
	spdlog::info("=============Authorizer Entity: {}", kvpairs[2]);
	spdlog::info("=============Authorizer IP: {}", kvpairs[3]);
#endif
	
    int checkActive = wf_inst->checkRemoteSCPStatus(kvpairs[3]);
    if (checkActive) {
        wf_inst->sendHashForAttestation(kvpairs[3]);
        rsp = "Authorization request sent";
        http_code = 200;
    }
    else {
#if INFO_IS_ON
        spdlog::info("Failed to connect to remote WAVE SCP");
#endif
        rsp = "Couldn't connect to remote WAVE SCP for Auth Req";
        http_code = 503;
    }
};


void WAVEHandlers::receive_auth_request (
			const std::string& request_main, 
            const std::string& clientIP, 
            std::string& rsp, 
			int& http_code) 
{

#if DEBUG_IS_ON
	spdlog::debug("Incoming authorization request from IP {}", clientIP);
	spdlog::debug("============Requester Hash: {}", request_main);
#endif

    std::vector<std::string> kvpairs;
    boost::split(kvpairs, request_main, boost::is_any_of("&"), boost::token_compress_on);
	
    wf_inst->createWAVEAttestation(kvpairs[0], clientIP, rsp);
    if(rsp.compare("yes")==0) {
#if DEBUG_IS_ON
        spdlog::debug("Sending hash for authorization acknowledgement to requester WAVE SCP at IP: {}", clientIP);
#endif
        wf_inst->sendAuthAck(clientIP, rsp);
    }

};

void WAVEHandlers::receive_ack_auth (
			const std::string& request_main, 
            const std::string& clientIP, 
            std::string& rsp, 
			int& http_code) 
{

#if DEBUG_IS_ON
	spdlog::debug("Incoming authorization acknowledgement from the authorizer WAVE SCP");
#endif

    std::vector<std::string> kvpairs;
    boost::split(kvpairs, request_main, boost::is_any_of("&"), boost::token_compress_on);
#if DEBUG_IS_ON
	spdlog::debug("============Attestation Hash: {}", kvpairs[0]);
	spdlog::debug("============Authorizer IP: {}", clientIP);
#endif

    wf_inst->receiveAuthAck(clientIP, kvpairs[0]);
};


void WAVEHandlers::handle_check_auth (
            const std::string& clientIP, 
            std::string& rsp, 
			int& http_code) {

#if DEBUG_IS_ON
	spdlog::debug("Checking if incoming request is authorized");
	spdlog::debug("============Sender IP: {}", clientIP);
#endif
    wf_inst->verifyWAVEAttestation(clientIP, rsp);

};

/*void WAVEHandlers::request_service (
			const std::string& request_main, 
            std::string& rsp, 
			int& http_code) 
{
    spdlog::debug("Requesting for service"); 
    // instead of hash, send IP address and map IP to hash
    
    std::vector<std::string> kvpairs;
    boost::split(kvpairs, request_main, boost::is_any_of("&"), boost::token_compress_on);

	spdlog::info("=============Requester Entity: {}", kvpairs[0]);
	spdlog::info("=============Requester IP: {}", kvpairs[1]);
	spdlog::info("=============Authorizer Entity: {}", kvpairs[2]);
	spdlog::info("=============Authorizer IP: {}", kvpairs[3]);
	
    wf_inst->requestService(kvpairs[1], kvpairs[3]);

};*/

/*void WAVEHandlers::send_acknowledge_auth (
            const std::string& request_main, std::string& rsp, 
            int& http_code, const uint8_t http_version) {
        

    std::vector<std::string> kvpairs;
    boost::split(kvpairs, request_main, boost::is_any_of("&"), boost::token_compress_on);
        
    spdlog::debug("Sending authorization acknowledgement to downstream WAVE SCP at IP: {}", kvpairs[1]);
    spdlog::info("=============Authorizer IP: {}", kvpairs[0]);
    spdlog::info("=============Requester IP: {}", kvpairs[1]);
    spdlog::info("Sending hashes as authorization ACK");
    
    wf_inst->sendHashesForProof(kvpairs[0], kvpairs[1]);
};*/

