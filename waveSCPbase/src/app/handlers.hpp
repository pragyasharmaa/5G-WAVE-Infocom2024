/*
 * Base development module for the WAVE/OAI integration side-car proxy
 *
 * ! file handlers.hpp
 *  \brief
 * \author: Tolga Omer Atalay
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/

#ifndef FILE_HANDLERS_HPP_SEEN
#define FILE_HANDLERS_HPP_SEEN

#include <string>
#include <iostream>

#include "spdlog/spdlog.h"

#include "functions.hpp" //this is the other class we design to carry out our functionalities by the receiving the preprocessed information from this one

#include <gmp.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

class WAVEHandlers {
    public: 
        static void send_discovery_auth_rqst(
                const std::string& request_main, 
                std::string& rsp, 
                int& http_code, 
                const uint8_t http_version);

        static void receive_auth_request(
                const std::string& request_main, 
                const std::string& clientIP, 
                std::string& rsp, 
                int& http_code);

        static void receive_ack_auth (
                const std::string& request_main, 
                const std::string& clientIP, 
                std::string& rsp, 
                int& http_code); 

        static void handle_check_auth(
                const std::string& clientIP, 
                std::string& rsp, 
                int& http_code);
        
        //static void request_service(const std::string& request_main, std::string& rsp, int& http_code);

};

#endif


