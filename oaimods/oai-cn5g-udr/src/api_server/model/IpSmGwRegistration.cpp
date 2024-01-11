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

#include "IpSmGwRegistration.h"

namespace oai::udr::model {

IpSmGwRegistration::IpSmGwRegistration() {
  m_IpSmGwMapAddress = "";
  m_IpSmGwMapAddressIsSet = false;
  m_IpSmGwDiameterAddressIsSet = false;
  m_UnriIndicator = false;
  m_UnriIndicatorIsSet = false;
}

IpSmGwRegistration::~IpSmGwRegistration() {}

void IpSmGwRegistration::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json &j, const IpSmGwRegistration &o) {
  j = nlohmann::json();
  if (o.ipSmGwMapAddressIsSet())
    j["ipSmGwMapAddress"] = o.m_IpSmGwMapAddress;
  if (o.ipSmGwDiameterAddressIsSet())
    j["ipSmGwDiameterAddress"] = o.m_IpSmGwDiameterAddress;
  if (o.unriIndicatorIsSet())
    j["unriIndicator"] = o.m_UnriIndicator;
}

void from_json(const nlohmann::json &j, IpSmGwRegistration &o) {
  if (j.find("ipSmGwMapAddress") != j.end()) {
    j.at("ipSmGwMapAddress").get_to(o.m_IpSmGwMapAddress);
    o.m_IpSmGwMapAddressIsSet = true;
  }
  if (j.find("ipSmGwDiameterAddress") != j.end()) {
    j.at("ipSmGwDiameterAddress").get_to(o.m_IpSmGwDiameterAddress);
    o.m_IpSmGwDiameterAddressIsSet = true;
  }
  if (j.find("unriIndicator") != j.end()) {
    j.at("unriIndicator").get_to(o.m_UnriIndicator);
    o.m_UnriIndicatorIsSet = true;
  }
}

std::string IpSmGwRegistration::getIpSmGwMapAddress() const {
  return m_IpSmGwMapAddress;
}
void IpSmGwRegistration::setIpSmGwMapAddress(std::string const &value) {
  m_IpSmGwMapAddress = value;
  m_IpSmGwMapAddressIsSet = true;
}
bool IpSmGwRegistration::ipSmGwMapAddressIsSet() const {
  return m_IpSmGwMapAddressIsSet;
}
void IpSmGwRegistration::unsetIpSmGwMapAddress() {
  m_IpSmGwMapAddressIsSet = false;
}
NetworkNodeDiameterAddress
IpSmGwRegistration::getIpSmGwDiameterAddress() const {
  return m_IpSmGwDiameterAddress;
}
void IpSmGwRegistration::setIpSmGwDiameterAddress(
    NetworkNodeDiameterAddress const &value) {
  m_IpSmGwDiameterAddress = value;
  m_IpSmGwDiameterAddressIsSet = true;
}
bool IpSmGwRegistration::ipSmGwDiameterAddressIsSet() const {
  return m_IpSmGwDiameterAddressIsSet;
}
void IpSmGwRegistration::unsetIpSmGwDiameterAddress() {
  m_IpSmGwDiameterAddressIsSet = false;
}
bool IpSmGwRegistration::isUnriIndicator() const { return m_UnriIndicator; }
void IpSmGwRegistration::setUnriIndicator(bool const value) {
  m_UnriIndicator = value;
  m_UnriIndicatorIsSet = true;
}
bool IpSmGwRegistration::unriIndicatorIsSet() const {
  return m_UnriIndicatorIsSet;
}
void IpSmGwRegistration::unsetUnriIndicator() { m_UnriIndicatorIsSet = false; }

} // namespace oai::udr::model
