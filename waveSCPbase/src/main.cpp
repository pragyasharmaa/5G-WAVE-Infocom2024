/*
 * Base development module for the WAVE/OAI integration side-car proxy 
 *
 * ! file main.cpp
 *  \brief
 * \author: Tolga Atalay 
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "rapidjson/document.h"

#include <iostream>
#include "spdlog/spdlog.h"

#include "handlers.hpp"
#include <thread>

using namespace Pistache;

//The first API receive function which will receive the request and forward it to the internal handler function
void handle_discovery_meta(const Rest::Request& req, Http::ResponseWriter resp) {

#if DEBUG_IS_ON
    spdlog::debug("Receiving Input: {}", req.body());
#endif
    std::string response_send;
    int http_code;

    WAVEHandlers::send_discovery_auth_rqst(req.body(), response_send, http_code, 1);
    if (http_code == 503) resp.send(Pistache::Http::Code::Service_Unavailable, response_send);
    else resp.send(Pistache::Http::Code::Ok, response_send);

}

void handle_reqauth(const Rest::Request& req, Http::ResponseWriter resp) {

#if DEBUG_IS_ON
    spdlog::debug("Receiving Auth Request: {} from client {}", req.body(), req.address().host());
    //spdlog::debug("Request resource is : {} ", req.resource());
#endif
    std::string response_send;
    int http_code;

    WAVEHandlers::receive_auth_request(req.body(), req.address().host(), response_send, http_code);
    resp.send(Pistache::Http::Code::Ok, response_send);

}


void handle_receiveauth(const Rest::Request& req, Http::ResponseWriter resp) {

#if DEBUG_IS_ON
    spdlog::debug("Receiving Auth: {}", req.body());
#endif
    std::string response_send;
    int http_code;

    WAVEHandlers::receive_ack_auth (req.body(), req.address().host(), response_send, http_code);
    resp.send(Pistache::Http::Code::Ok, response_send);

}

void handle_checkauth(const Rest::Request& req, Http::ResponseWriter resp) {

#if DEBUG_IS_ON
    spdlog::debug("Receiving Client IP: {}", req.body());
#endif
    std::string response_send;
    int http_code;

    WAVEHandlers::handle_check_auth(req.body(), response_send, http_code);
    if (response_send.compare("1") == 0) {
        resp.send(Pistache::Http::Code::Ok, response_send);
    }
    else {
        resp.send(Pistache::Http::Code::Forbidden, response_send);
        
    }

}

/*void handle_sendauth(const Rest::Request& req, Http::ResponseWriter resp) {

    spdlog::debug("Receiving Input: {}", req.body());
    std::string response_send;
    int http_code;

    WAVEHandlers::send_acknowledge_auth (req.body(), response_send, http_code, 1);
    resp.send(Pistache::Http::Code::Ok, response_send);

}*/

/*void handle_reqservice(const Rest::Request& req, Http::ResponseWriter resp) {

    spdlog::debug("Receiving Input: {}", req.body());
    std::string response_send;
    int http_code;

    WAVEHandlers::request_service(req.body(), response_send, http_code);
    resp.send(Pistache::Http::Code::Ok, response_send);

}*/

void default_handler (const Rest::Request& req, Http::ResponseWriter resp){

#if DEBUG_IS_ON
    spdlog::debug("Triggering default router, HTTP request from client: {}", req.address().host());
#endif
    std::string response_send;
    int http_code;

    resp.send(Pistache::Http::Code::Ok, "Default done");

}

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::debug); // debugger option level
    using namespace Rest; // selecting namespace for the Pistache class

    Router router; // Pistache - router object
    Port port(10095); // select port 
    Address addr(Ipv4::any(), port); // select IPv4 address -- in this case, listen on all the local virtual network interfaces
    std::shared_ptr<Http::Endpoint> endpoint = std::make_shared<Http::Endpoint>(addr); //create the endpoint object and assign it the address object created above
    //auto opts = Http::Endpoint::options().threads(std::thread::hardware_concurrency()); //set options -- http server thread count
    auto opts = Http::Endpoint::options().threads(6); //set options -- http server thread count
    opts.flags(Pistache::Tcp::Options::ReuseAddr); // set TCP reuse options to avoid "address already in use" (will be required in the case of multiple handlers, this sample code only has one for now but we will need it later)
    endpoint->init(opts); // assign the set options to the endpoint

    Routes::Post(router, "/oai/discoverdata", Routes::bind(handle_discovery_meta)); //receive discovery metadata from OAI compoennts
    Routes::Post(router, "/wave/authreq", Routes::bind(handle_reqauth)); //receive authorization request from another wave SCP
    Routes::Post(router, "/wave/authack", Routes::bind(handle_receiveauth)); //receive authorization acknowledgement from attester wave SCP
    Routes::Post(router, "/wave/checkauth", Routes::bind(handle_checkauth)); //check authorization status endpoint
    //Routes::Post(router, "/wave/sendauthack", Routes::bind(handle_sendauth)); //send authorization acknowledgement to requester wave SCP
    //Routes::Post(router, "/oai/reqservice", Routes::bind(handle_reqservice)); //send request for service

    router.addCustomHandler(Routes::bind(&default_handler));

    spdlog::info("Starting HTTP Server for WAVE-5G SCP"); //this is a logger which will print debug messages during run-time 
    endpoint->setHandler(router.handler()); //set the handler 
    endpoint->serve();//start the http server
}
