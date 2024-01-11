/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 *file except in compliance with the License. You may obtain a copy of the
 *License at
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

/*! \file udm_config.cpp
 \brief
 \author  Hongxin WANG, BUPT
 \date 2021
 \email: contact@openairinterface.org
 */

#include "udm_config.hpp"

#include <iostream>
#include <libconfig.h++>

#include "if.hpp"
#include "logger.hpp"
#include "fqdn.hpp"
#include "string.hpp"
#include <curl/curl.h>

extern "C" {
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "common_defs.h"
}



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

namespace oai::udm::config {

//------------------------------------------------------------------------------
udm_config::udm_config() : instance(0), pid_dir(), udm_name(), sbi() {
  udr_addr.ipv4_addr.s_addr = INADDR_ANY;
  udr_addr.port             = 80;
  udr_addr.api_version      = "v1";
  udr_addr.fqdn             = {};
  use_fqdn_dns              = false;
}

//------------------------------------------------------------------------------
udm_config::~udm_config() {}

//------------------------------------------------------------------------------
int udm_config::load(const std::string& config_file) {
  Logger::config().debug(
      "\nLoad UDM system configuration file(%s)", config_file.c_str());
  Config cfg;
  unsigned char buf_in6_addr[sizeof(struct in6_addr)];

  try {
    cfg.readFile(config_file.c_str());
  } catch (const FileIOException& fioex) {
    Logger::config().error(
        "I/O error while reading file %s - %s", config_file.c_str(),
        fioex.what());
    throw;
  } catch (const ParseException& pex) {
    Logger::config().error(
        "Parse error at %s:%d - %s", pex.getFile(), pex.getLine(),
        pex.getError());
    throw;
  }
  const Setting& root = cfg.getRoot();

  try {
    const Setting& udm_cfg = root[UDM_CONFIG_STRING_UDM_CONFIG];
  } catch (const SettingNotFoundException& nfex) {
    Logger::config().error("%s : %s", nfex.what(), nfex.getPath());
    return RETURNerror;
  }
  const Setting& udm_cfg = root[UDM_CONFIG_STRING_UDM_CONFIG];
  try {
    udm_cfg.lookupValue(UDM_CONFIG_STRING_INSTANCE_ID, instance);
  } catch (const SettingNotFoundException& nfex) {
    Logger::config().error(
        "%s : %s, using defaults", nfex.what(), nfex.getPath());
  }

  try {
    udm_cfg.lookupValue(UDM_CONFIG_STRING_PID_DIRECTORY, pid_dir);
  } catch (const SettingNotFoundException& nfex) {
    Logger::config().error(
        "%s : %s, using defaults", nfex.what(), nfex.getPath());
  }
  try {
    udm_cfg.lookupValue(UDM_CONFIG_STRING_UDM_NAME, udm_name);
  } catch (const SettingNotFoundException& nfex) {
    Logger::config().error(
        "%s : %s, using defaults", nfex.what(), nfex.getPath());
  }

  try {
    const Setting& new_if_cfg = udm_cfg[UDM_CONFIG_STRING_INTERFACES];

    const Setting& sbi_udm_cfg =
        new_if_cfg[UDM_CONFIG_STRING_INTERFACE_SBI_UDM];
    load_interface(sbi_udm_cfg, sbi);

  } catch (const SettingNotFoundException& nfex) {
    Logger::config().error(
        "%s : %s, using defaults", nfex.what(), nfex.getPath());
    return RETURNerror;
  }

  // Support features
  try {
    const Setting& support_features =
        udm_cfg[UDM_CONFIG_STRING_SUPPORT_FEATURES];
    std::string opt = {};

    support_features.lookupValue(
        UDM_CONFIG_STRING_SUPPORT_FEATURES_USE_FQDN_DNS, opt);
    if (boost::iequals(opt, "yes")) {
      use_fqdn_dns = true;
    } else {
      use_fqdn_dns = false;
    }

  } catch (const SettingNotFoundException& nfex) {
    Logger::udm_app().error(
        "%s : %s, using defaults", nfex.what(), nfex.getPath());
    return RETURNerror;
  }

  try {
    std::string astring;

    // UDR
    const Setting& udr_cfg       = udm_cfg[UDM_CONFIG_STRING_UDR];
    struct in_addr udr_ipv4_addr = {};
    unsigned int udr_port        = 0;
    std::string udr_api_version  = {};

    if (!use_fqdn_dns) {
      udr_cfg.lookupValue(UDM_CONFIG_STRING_UDR_IPV4_ADDRESS, astring);
      IPV4_STR_ADDR_TO_INADDR(
          util::trim(astring).c_str(), udr_ipv4_addr,
          "BAD IPv4 ADDRESS FORMAT FOR UDR !");
      udr_addr.ipv4_addr = udr_ipv4_addr;
      if (!(udr_cfg.lookupValue(UDM_CONFIG_STRING_UDR_PORT, udr_port))) {
        Logger::udm_app().error(UDM_CONFIG_STRING_UDR_PORT "failed");
        throw(UDM_CONFIG_STRING_UDR_PORT "failed");
      }
      udr_addr.port = udr_port;

      if (!(udr_cfg.lookupValue(
              UDM_CONFIG_STRING_API_VERSION, udr_api_version))) {
        Logger::udm_app().error(UDM_CONFIG_STRING_API_VERSION "failed");
        throw(UDM_CONFIG_STRING_API_VERSION "failed");
      }
      udr_addr.api_version = udr_api_version;
    } else {
      udr_cfg.lookupValue(UDM_CONFIG_STRING_FQDN_DNS, astring);
      uint8_t addr_type   = {0};
      std::string address = {};
      fqdn::resolve(astring, address, udr_port, addr_type);
      if (addr_type != 0) {  // IPv6
        // TODO:
        throw("DO NOT SUPPORT IPV6 ADDR FOR UDR!");
      } else {  // IPv4
        IPV4_STR_ADDR_TO_INADDR(
            util::trim(address).c_str(), udr_ipv4_addr,
            "BAD IPv4 ADDRESS FORMAT FOR UDR !");
        udr_addr.ipv4_addr          = udr_ipv4_addr;
        udr_addr.port               = udr_port;
        std::string udr_api_version = {};
        if (!(udr_cfg.lookupValue(
                UDM_CONFIG_STRING_API_VERSION, udr_api_version))) {
          Logger::udm_app().error(UDM_CONFIG_STRING_API_VERSION "failed");
          throw(UDM_CONFIG_STRING_API_VERSION "failed");
        }
        udr_addr.api_version =
            udr_api_version;  // TODO: to get API version from DNS
        udr_addr.fqdn = astring;
      }
    }

  } catch (const SettingNotFoundException& nfex) {
    Logger::udm_app().error("%s : %s", nfex.what(), nfex.getPath());
    return RETURNerror;
  }
  return RETURNok;
}

//------------------------------------------------------------------------------
void udm_config::display() {
  Logger::config().info(
      "==== OAI-CN5G %s v%s ====", PACKAGE_NAME, PACKAGE_VERSION);
  Logger::config().info("============== UDM =============");
  Logger::config().info("Configuration UDM:");
  Logger::config().info("- Instance................: %d", instance);
  Logger::config().info("- PID Dir.................: %s", pid_dir.c_str());
  Logger::config().info("- UDM name................: %s", udm_name.c_str());

  Logger::config().info("- SBI:");
  Logger::config().info("    Iface name............: %s", sbi.if_name.c_str());
  Logger::config().info("    IPv4 Addr.............: %s", inet_ntoa(sbi.addr4));
  Logger::config().info("    Port..................: %d", sbi.port);

  Logger::config().info("- UDR:");
  Logger::config().info(
      "    IPv4 Addr.............: %s",
      inet_ntoa(*((struct in_addr*) &udr_addr.ipv4_addr)));
  Logger::config().info("    Port..................: %lu  ", udr_addr.port);
  Logger::config().info(
      "    API version...........: %s", udr_addr.api_version.c_str());
  if (use_fqdn_dns)
    Logger::config().info(
        "    FQDN..................: %s", udr_addr.fqdn.c_str());
}

//------------------------------------------------------------------------------
int udm_config::load_interface(
    const libconfig::Setting& if_cfg, interface_cfg_t& cfg) {
  if_cfg.lookupValue(UDM_CONFIG_STRING_INTERFACE_NAME, cfg.if_name);
  util::trim(cfg.if_name);
  if (not boost::iequals(cfg.if_name, "none")) {
    std::string address = {};
    if_cfg.lookupValue(UDM_CONFIG_STRING_IPV4_ADDRESS, address);
    util::trim(address);
    if (boost::iequals(address, "read")) {
      if (get_inet_addr_infos_from_iface(
              cfg.if_name, cfg.addr4, cfg.network4, cfg.mtu)) {
        Logger::config().error(
            "Could not read %s network interface configuration", cfg.if_name);
        return RETURNerror;
      }
    } else {
      std::vector<std::string> words;
      boost::split(
          words, address, boost::is_any_of("/"), boost::token_compress_on);
      if (words.size() != 2) {
        Logger::config().error(
            "Bad value " UDM_CONFIG_STRING_IPV4_ADDRESS " = %s in config file",
            address.c_str());
        return RETURNerror;
      }
      unsigned char buf_in_addr[sizeof(struct in6_addr)];  // you never know...
      if (inet_pton(AF_INET, util::trim(words.at(0)).c_str(), buf_in_addr) ==
          1) {
        memcpy(&cfg.addr4, buf_in_addr, sizeof(struct in_addr));
      } else {
        Logger::config().error(
            "In conversion: Bad value " UDM_CONFIG_STRING_IPV4_ADDRESS
            " = %s in config file",
            util::trim(words.at(0)).c_str());
        return RETURNerror;
      }
      cfg.network4.s_addr = htons(
          ntohs(cfg.addr4.s_addr) &
          0xFFFFFFFF << (32 - std::stoi(util::trim(words.at(1)))));
    }
    if_cfg.lookupValue(UDM_CONFIG_STRING_PORT, cfg.port);

    // SBI API VERSION
    if (!(if_cfg.lookupValue(UDM_CONFIG_STRING_API_VERSION, cfg.api_version))) {
      Logger::config().error(UDM_CONFIG_STRING_API_VERSION "failed");
      throw(UDM_CONFIG_STRING_API_VERSION "failed");
    }
  }
  return RETURNok;
}

//function added to send the information to the SCP
void udm_config::send_profile_toSCP () {
        //Get IP Addresses for Remote Servers
        const char *tmp1 = getenv("WAVE_L_IP");
        std::string WLIP(tmp1 ? tmp1 : "");
        if (WLIP.empty()) {
                Logger::config().error("WAVE local server IP not found");
                exit(EXIT_FAILURE);
        }
        Logger::config().info("WAVE local server IP is : %s", WLIP.c_str());

        const char *tmp2 = getenv("WAVE_R_IP");
        std::string WRIP(tmp2 ? tmp2 : "");
        if (WRIP.empty()) {
                Logger::config().error("WAVE-SCP server IP not found");
                exit(EXIT_FAILURE);
        }
        Logger::config().info("WAVE-SCP server IP is : %s", WRIP.c_str());

        const char *tmp3 = getenv("WAVE_SCP_PORT");
        std::string WSPORT(tmp3 ? tmp3 : "");
        if (WSPORT.empty()) {
                Logger::config().error("WAVE-SCP server port not found");
                exit(EXIT_FAILURE);
        }
        Logger::config().info("WAVE remote server port is : %s", WSPORT.c_str());

        std::string uriwl = "http://" + WLIP + ":" + WSPORT + "/oai/discoverdata";
        std::string wl_send_1 = std::string("UDM") + "&" + std::string(inet_ntoa(sbi.addr4)) + "&" + std::string("UDR") + "&" + std::string(inet_ntoa(udr_addr.ipv4_addr));
        std::string wl_send_2 = std::string("UDM") + "&" + std::string(inet_ntoa(sbi.addr4)) + "&" + std::string("AUSF") + "&" + std::string(WRIP.c_str());
        std::string wl_resp;

        Logger::config().info("Sending the profile information to the Local WAVE SCP");

        send_custom_curl(uriwl, wl_send_1, wl_resp);
        Logger::config().info("Received response from Local WAVE SCP: %s", wl_resp.c_str());

        send_custom_curl(uriwl, wl_send_2, wl_resp);
        Logger::config().info("Received response from Local WAVE SCP: %s", wl_resp.c_str());
}
//----------------------------------------------------------------------------



}  // namespace oai::udm::config
