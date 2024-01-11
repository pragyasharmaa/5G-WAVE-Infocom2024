/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the
 * License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#include "udr_config.hpp"

#include <iostream>
#include <libconfig.h++>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include "common_defs.h"
#include "if.hpp"
#include "logger.hpp"
#include "string.hpp"
#include <curl/curl.h>

const char *wlip = "WAVE_L_IP";
const char *wrip = "WAVE_R_IP";
const char *wsport = "WAVE_SCP_PORT";

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
}

void send_custom_curl(std::string& uri, std::string& message, std::string& response) {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;

        struct curl_slist *slist1;
        slist1 = NULL;
        slist1 = curl_slist_append(slist1, "Content-Type: application/json");

        curl = curl_easy_init();

        if(curl) {
                curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
                curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 1000L);
                curl_easy_setopt(curl, CURLOPT_POST, 1);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
        }
        response = readBuffer;
}


using namespace libconfig;

namespace oai::udr::config {

//------------------------------------------------------------------------------
udr_config::udr_config() : mysql(), instance(), pid_dir(), nudr() {
  nudr_http2_port = 8080;
  nudr.api_version = "v1";
}

//------------------------------------------------------------------------------
udr_config::~udr_config() {}

//------------------------------------------------------------------------------
int udr_config::load(const std ::string &config_file) {
  Logger::udr_app().debug("\nLoad UDR system configuration file(%s)",
                          config_file.c_str());

  Config cfg;
  unsigned char buf_in6_addr[sizeof(struct in6_addr)];

  // Read the file. If there is an error, report it and exit.
  try {
    cfg.readFile(config_file.c_str());
  } catch (const FileIOException &fioex) {
    Logger::udr_app().error("I/O error while reading file %s - %s",
                            config_file.c_str(), fioex.what());
    throw;
  } catch (const ParseException &pex) {
    Logger::udr_app().error("Parse error at %s:%d - %s", pex.getFile(),
                            pex.getLine(), pex.getError());
    throw;
  }
  const Setting &root = cfg.getRoot();
  try {
    const Setting &udr_cfg = root[UDR_CONFIG_STRING_UDR_CONFIG];
  } catch (const SettingNotFoundException &nfex) {
    Logger::udr_app().error("%s : %s", nfex.what(), nfex.getPath());
    return RETURNerror;
  }
  const Setting &udr_cfg = root[UDR_CONFIG_STRING_UDR_CONFIG];
  try {
    udr_cfg.lookupValue(UDR_CONFIG_STRING_INSTANCE_ID, instance);
  } catch (const SettingNotFoundException &nfex) {
    Logger::udr_app().error("%s : %s, using defaults", nfex.what(),
                            nfex.getPath());
  }
  try {
    udr_cfg.lookupValue(UDR_CONFIG_STRING_PID_DIRECTORY, pid_dir);
  } catch (const SettingNotFoundException &nfex) {
    Logger::udr_app().error("%s : %s, using defaults", nfex.what(),
                            nfex.getPath());
  }

  try {
    const Setting &new_if_cfg = udr_cfg[UDR_CONFIG_STRING_INTERFACES];
    const Setting &nudr_cfg = new_if_cfg[UDR_CONFIG_STRING_INTERFACE_NUDR];
    load_interface(nudr_cfg, nudr);
    // HTTP2 port
    if (!(nudr_cfg.lookupValue(UDR_CONFIG_STRING_HTTP2_PORT,
                               nudr_http2_port))) {
      Logger::udr_app().error(UDR_CONFIG_STRING_HTTP2_PORT "failed");
      throw(UDR_CONFIG_STRING_HTTP2_PORT "failed");
    }

  } catch (const SettingNotFoundException &nfex) {
    Logger::udr_app().error("%s : %s, using defaults", nfex.what(),
                            nfex.getPath());
    return RETURNerror;
  }

  try {
    const Setting &mysql_cfg = udr_cfg[UDR_CONFIG_STRING_MYSQL];
    mysql_cfg.lookupValue(UDR_CONFIG_STRING_MYSQL_SERVER, mysql.mysql_server);
    mysql_cfg.lookupValue(UDR_CONFIG_STRING_MYSQL_USER, mysql.mysql_user);
    mysql_cfg.lookupValue(UDR_CONFIG_STRING_MYSQL_PASS, mysql.mysql_pass);
    mysql_cfg.lookupValue(UDR_CONFIG_STRING_MYSQL_DB, mysql.mysql_db);
  } catch (const SettingNotFoundException &nfex) {
    Logger::udr_app().error("%s : %s, using defaults", nfex.what(),
                            nfex.getPath());
    return RETURNerror;
  }

  return RETURNok;
}

//------------------------------------------------------------------------------
int udr_config::load_interface(const libconfig::Setting &if_cfg,
                               interface_cfg_t &cfg) {
  if_cfg.lookupValue(UDR_CONFIG_STRING_INTERFACE_NAME, cfg.if_name);
  util::trim(cfg.if_name);
  if (not boost::iequals(cfg.if_name, "none")) {
    std::string address = {};
    if_cfg.lookupValue(UDR_CONFIG_STRING_IPV4_ADDRESS, address);
    util::trim(address);
    if (boost::iequals(address, "read")) {
      if (get_inet_addr_infos_from_iface(cfg.if_name, cfg.addr4, cfg.network4,
                                         cfg.mtu)) {
        Logger::udr_app().error(
            "Could not read %s network interface configuration", cfg.if_name);
        return RETURNerror;
      }
    } else {
      std::vector<std::string> words = {};
      boost::split(words, address, boost::is_any_of("/"),
                   boost::token_compress_on);
      if (words.size() != 2) {
        Logger::udr_app().error("Bad value " UDR_CONFIG_STRING_IPV4_ADDRESS
                                " = %s in config file",
                                address.c_str());
        return RETURNerror;
      }
      unsigned char buf_in_addr[sizeof(struct in6_addr)]; // you never know...
      if (inet_pton(AF_INET, util::trim(words.at(0)).c_str(), buf_in_addr) ==
          1) {
        memcpy(&cfg.addr4, buf_in_addr, sizeof(struct in_addr));
      } else {
        Logger::udr_app().error(
            "In conversion: Bad value " UDR_CONFIG_STRING_IPV4_ADDRESS
            " = %s in config file",
            util::trim(words.at(0)).c_str());
        return RETURNerror;
      }
      cfg.network4.s_addr =
          htons(ntohs(cfg.addr4.s_addr) &
                0xFFFFFFFF << (32 - std::stoi(util::trim(words.at(1)))));
    }
    if_cfg.lookupValue(UDR_CONFIG_STRING_PORT, cfg.port);

    // API VERSION
    if (!(if_cfg.lookupValue(UDR_CONFIG_STRING_API_VERSION, cfg.api_version))) {
      Logger::udr_app().error(UDR_CONFIG_STRING_API_VERSION "failed");
      throw(UDR_CONFIG_STRING_API_VERSION "failed");
    }
  }
  return RETURNok;
}

//------------------------------------------------------------------------------
void udr_config::display() {
  Logger::config().info("==== OAI-CN5G %s v%s ====", PACKAGE_NAME,
                        PACKAGE_VERSION);
  Logger::config().info(
      "======================    UDR   =====================");
  Logger::config().info("Configuration UDR:");
  Logger::config().info(
      "- Instance ...........................................: %d", instance);
  Logger::config().info(
      "- PID dir ............................................: %s",
      pid_dir.c_str());

  Logger::config().info("- Nudr Networking:");
  Logger::config().info("    Interface name ......: %s", nudr.if_name.c_str());
  Logger::config().info("    IPv4 Addr ...........: %s", inet_ntoa(nudr.addr4));
  Logger::config().info("    Port ................: %d", nudr.port);
  Logger::config().info("    HTTP2 port ..........: %d", nudr_http2_port);
  Logger::config().info("    API version..........: %s",
                        nudr.api_version.c_str());

  Logger::config().info(
      "- MYSQL Server Addr...................................: %s",
      mysql.mysql_server.c_str());
  Logger::config().info(
      "- MYSQL user .........................................: %s",
      mysql.mysql_user.c_str());
  Logger::config().info(
      "- MYSQL pass .........................................: %s",
      mysql.mysql_pass.c_str());
  Logger::config().info(
      "- MYSQL db ...........................................: %s",
      mysql.mysql_db.c_str());
}

//----------------------------------------------------------------------------
//function added to send the information to the SCP
void udr_config::send_profile_toSCP () {
        //Get IP Addresses for Remote Servers
        const char *tmp1 = getenv("WAVE_L_IP");
        std::string WLIP(tmp1 ? tmp1 : "");
        if (WLIP.empty()) {
		Logger::udr_app().error("WAVE local server IP not found");
                exit(EXIT_FAILURE);
        }
        Logger::udr_app().info("WAVE local server IP is : %s", WLIP.c_str());
        
	const char *tmp2 = getenv("WAVE_R_IP");
        std::string WRIP(tmp2 ? tmp2 : "");
        if (WRIP.empty()) {
		Logger::udr_app().error("WAVE-SCP server IP not found");
                exit(EXIT_FAILURE);
        }
        Logger::udr_app().info("WAVE-SCP server IP is : %s", WRIP.c_str());
	
	const char *tmp3 = getenv("WAVE_SCP_PORT");
        std::string WSPORT(tmp3 ? tmp3 : "");
        if (WSPORT.empty()) {
		Logger::udr_app().error("WAVE-SCP server port not found");
                exit(EXIT_FAILURE);
        }
        Logger::udr_app().info("WAVE remote server port is : %s", WSPORT.c_str());

        std::string uriwl = "http://" + WLIP + ":" + WSPORT + "/oai/discoverdata";
	std::string wl_send = std::string("UDR") + "&" + std::string(inet_ntoa(nudr.addr4)) + "&" + std::string("UDM") + "&" + std::string(WRIP.c_str());	
	std::string wl_resp;

        Logger::udr_app().info("Sending the profile information to the Local WAVE SCP");

	send_custom_curl(uriwl, wl_send, wl_resp);
        
	Logger::udr_app().info("Received response from Local WAVE SCP: %s", wl_resp.c_str());
}
//----------------------------------------------------------------------------

} // namespace oai::udr::config
