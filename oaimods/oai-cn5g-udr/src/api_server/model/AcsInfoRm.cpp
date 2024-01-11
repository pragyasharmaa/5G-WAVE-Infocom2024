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
/**
 * Nudr_DataRepository API OpenAPI file
 * Unified Data Repository Service. © 2020, 3GPP Organizational Partners (ARIB,
 * ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 2.1.2
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "AcsInfoRm.h"

namespace oai::udr::model {

AcsInfoRm::AcsInfoRm() {
  m_AcsUrl = "";
  m_AcsUrlIsSet = false;
  m_AcsIpv4Addr = "";
  m_AcsIpv4AddrIsSet = false;
  m_AcsIpv6AddrIsSet = false;
}

AcsInfoRm::~AcsInfoRm() {}

void AcsInfoRm::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json &j, const AcsInfoRm &o) {
  j = nlohmann::json();
  if (o.acsUrlIsSet())
    j["acsUrl"] = o.m_AcsUrl;
  if (o.acsIpv4AddrIsSet())
    j["acsIpv4Addr"] = o.m_AcsIpv4Addr;
  if (o.acsIpv6AddrIsSet())
    j["acsIpv6Addr"] = o.m_AcsIpv6Addr;
}

void from_json(const nlohmann::json &j, AcsInfoRm &o) {
  if (j.find("acsUrl") != j.end()) {
    j.at("acsUrl").get_to(o.m_AcsUrl);
    o.m_AcsUrlIsSet = true;
  }
  if (j.find("acsIpv4Addr") != j.end()) {
    j.at("acsIpv4Addr").get_to(o.m_AcsIpv4Addr);
    o.m_AcsIpv4AddrIsSet = true;
  }
  if (j.find("acsIpv6Addr") != j.end()) {
    j.at("acsIpv6Addr").get_to(o.m_AcsIpv6Addr);
    o.m_AcsIpv6AddrIsSet = true;
  }
}

std::string AcsInfoRm::getAcsUrl() const { return m_AcsUrl; }
void AcsInfoRm::setAcsUrl(std::string const &value) {
  m_AcsUrl = value;
  m_AcsUrlIsSet = true;
}
bool AcsInfoRm::acsUrlIsSet() const { return m_AcsUrlIsSet; }
void AcsInfoRm::unsetAcsUrl() { m_AcsUrlIsSet = false; }
std::string AcsInfoRm::getAcsIpv4Addr() const { return m_AcsIpv4Addr; }
void AcsInfoRm::setAcsIpv4Addr(std::string const &value) {
  m_AcsIpv4Addr = value;
  m_AcsIpv4AddrIsSet = true;
}
bool AcsInfoRm::acsIpv4AddrIsSet() const { return m_AcsIpv4AddrIsSet; }
void AcsInfoRm::unsetAcsIpv4Addr() { m_AcsIpv4AddrIsSet = false; }
Ipv6Addr AcsInfoRm::getAcsIpv6Addr() const { return m_AcsIpv6Addr; }
void AcsInfoRm::setAcsIpv6Addr(Ipv6Addr const &value) {
  m_AcsIpv6Addr = value;
  m_AcsIpv6AddrIsSet = true;
}
bool AcsInfoRm::acsIpv6AddrIsSet() const { return m_AcsIpv6AddrIsSet; }
void AcsInfoRm::unsetAcsIpv6Addr() { m_AcsIpv6AddrIsSet = false; }

} // namespace oai::udr::model
