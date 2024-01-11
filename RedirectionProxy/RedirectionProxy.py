#!/usr/bin/python3
from http.server import BaseHTTPRequestHandler, HTTPServer
from socketserver import ThreadingMixIn
import threading
import logging
import netifaces
import json
import requests

req_id=0

def get_self_ip(iface):
    addresses = netifaces.ifaddresses(iface)
    ip = addresses.get(netifaces.AF_INET)
    return ip[0]['addr']

def get_url(content):
    split_ip = (str(content.headers)).split("Host: ")
    ip = split_ip[1].split("\n")
    url = "http://" + ip[0] + content.path
    return url

def forward_oai(request_body, request_type, request_url):
    response = requests.request(request_type, url=request_url, data=request_body)
    return response

# forwards the ip address of the sender to the WAVESCP
def send_ip_to_wave_scp(ip):
    url = "http://127.0.0.1:10095/wave/checkauth"
    response = requests.post(url=url, data=ip)
    return response

# method which redirects the request to WAVE SCP and then OAI (with some exceptions)
def request_redirector(content, request_body, request_type):
    path_received = content.path 
    request_url = get_url(content)
    ip_sender = content.client_address[0]
    ip_self = get_self_ip("net1") # net1 is the interface used in multus configuration for deployment
    # ip_self = get_self_ip("lo") 
     
    # No WAVE for 1. message to/from UPF  2. message from NRF  3. message from self OAI
    if ("nsmf-nfstatus-notify" in path_received) or (ip_sender == "10.100.17.10") or (ip_sender == ip_self):
        response = forward_oai(request_body, request_type, request_url)
        return response
   
    # Send IP address to WAVE SCP for verification of authorization
    # wave_verification = send_ip_to_wave_scp(ip_sender)

    # if verification response is "1", must send back the orig request as is, back to OAI.
    # if wave_verification.text == "1":
    if True:
        response = forward_oai(request_body, request_type, request_url)
        return response
    else:
        logging.info("Request not verified by WAVE")
        response = requests.models.Response()
        response.status_code = 403
        response.headers = {'Content-Type': 'text/html'}
        response._content = b"WAVE Verification failed"
        return response



# custom HTTP request handler class
class RedirectionProxyHandler(BaseHTTPRequestHandler):
    def default_method(self, req_id):
        request_client = self.client_address[0]
        request_host = self.headers.get('Host')
        request_path = self.path
        request_type = self.command;
        # logging.info("Request = %s, Client = %s, Host = %s, Type = %s, Path = %s \n", str(req_id), request_client, request_host, request_type, request_path)
        logging.info("Request;%s;Client;%s;Host;%s;Type;%s;Path;%s", str(req_id), request_client, request_host, request_type, request_path)

        content_length = int(self.headers.get('Content-Length', 0))  # Gets the size of data
        request_body = self.rfile.read(content_length)  # Gets the data itself
        request_headers = self.headers
        decoded_request_body = request_body.decode('utf-8', errors='replace') # Exception handling in bytearray decoding (if character is not in utf-8)

        # logging.info("Request\nClient: %s\nType: %s\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n\n",
                     # request_client, request_type, str(request_path), str(request_headers), decoded_request_body)

        # send the request forward
        resp = request_redirector(self, request_body, request_type)

        # logging.info("Response: \nBody: %s\n\nHeader: %s\nStatus Code: %s\n\n", 
                      # resp.text, str(resp.headers), str(resp.status_code))
        if resp:
            self.send_response(resp.status_code)
            for header_name, header_value in resp.headers.items():
                self.send_header(header_name, header_value)
            self.end_headers()
            self.wfile.write(resp.content)  # write the content (byte-like) to the body of the response
        else:
            handler_resp = "".encode()
            self.send_response(404)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(handler_resp)
        
        # logging.info("Response = %s\n--------------------------------------------------------------\n", str(req_id))
        logging.info("Response;%s", str(req_id))

    def do_HEAD(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_DELETE(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_PUT(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_GET(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_POST(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_PATCH(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_TRACE(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_CONNECT(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    def do_OPTIONS(self):
        global req_id
        req_id+=1
        self.default_method(req_id)

    # suppress logs of http server
    def log_request(self, code='-', size='-'): 
        return

class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """Handle requests in a separate thread."""
    pass


def run(server_class=ThreadedHTTPServer, handler_class=RedirectionProxyHandler, port=10096):
    log_format = "%(asctime)s;%(message)s"
    logging.basicConfig(level='INFO', format=log_format)

    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    logging.debug('Starting Proxy Server...\n')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    logging.debug('Stopping Proxy Server...\n')


if __name__ == '__main__':
    from sys import argv
    if len(argv) == 2:
        run(port=int(argv[1]))
    else:
        run()
