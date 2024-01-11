/*
 * Base development module for the WAVE/OAI integration side-car proxy
 *
 * ! file functions.hpp
 * \brief
 * \author: Tolga Atalay
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
 */

#ifndef FILE_FUNCTIONS_HPP_SEEN
#define FILE_FUNCTIONS_HPP_SEEN

#include <iostream>
#include <fstream>
#include <openssl/pem.h> 
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <cstdio>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <unordered_map>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include "curl/curl.h"


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
}

class WAVEfunctions {
    public:
        explicit WAVEfunctions();
        WAVEfunctions(WAVEfunctions const&) = delete;
        void operator=(WAVEfunctions const&) = delete;
        virtual ~WAVEfunctions();

        void send_custom_curl(
                std::string& uri, 
                std::string& message, 
                std::string& response);

        int checkRemoteSCPStatus(
                std::string& authorizerIP);

        void sendHashForAttestation(
                std::string& authorizerIP);

        void createWAVEAttestation(
                std::string& requesterHash, 
                const std::string& requesterIP, 
                std::string& rsp);

        void sendAuthAck(
                const std::string& requesterIP, 
                std::string& rsp);

        void receiveAuthAck(
                const std::string& authorizerIP,
                std::string& attestationHash);

        void verifyWAVEAttestation(
                const std::string& requesterIP, 
                std::string& rsp);
        
        //void requestService(std::string& sourceIP, std::string& targetIP); 
};

extern std::unordered_map<std::string, std::string> AttesterIP_To_AttestationHash;
extern std::unordered_map<std::string, std::string> RequesterIP_To_AttestationHash;
extern std::unordered_map<std::string, std::string> RequesterIP_To_RequesterHash;

#endif
