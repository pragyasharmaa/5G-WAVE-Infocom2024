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

#include "LcsPrivacyData.h"

namespace oai::udr::model {

LcsPrivacyData::LcsPrivacyData() {
  m_LpiIsSet = false;
  m_UnrelatedClassIsSet = false;
  m_PlmnOperatorClassesIsSet = false;
}

LcsPrivacyData::~LcsPrivacyData() {}

void LcsPrivacyData::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json &j, const LcsPrivacyData &o) {
  j = nlohmann::json();
  if (o.lpiIsSet())
    j["lpi"] = o.m_Lpi;
  if (o.unrelatedClassIsSet())
    j["unrelatedClass"] = o.m_UnrelatedClass;
  if (o.plmnOperatorClassesIsSet() || !o.m_PlmnOperatorClasses.empty())
    j["plmnOperatorClasses"] = o.m_PlmnOperatorClasses;
}

void from_json(const nlohmann::json &j, LcsPrivacyData &o) {
  if (j.find("lpi") != j.end()) {
    j.at("lpi").get_to(o.m_Lpi);
    o.m_LpiIsSet = true;
  }
  if (j.find("unrelatedClass") != j.end()) {
    j.at("unrelatedClass").get_to(o.m_UnrelatedClass);
    o.m_UnrelatedClassIsSet = true;
  }
  if (j.find("plmnOperatorClasses") != j.end()) {
    j.at("plmnOperatorClasses").get_to(o.m_PlmnOperatorClasses);
    o.m_PlmnOperatorClassesIsSet = true;
  }
}

Lpi LcsPrivacyData::getLpi() const { return m_Lpi; }
void LcsPrivacyData::setLpi(Lpi const &value) {
  m_Lpi = value;
  m_LpiIsSet = true;
}
bool LcsPrivacyData::lpiIsSet() const { return m_LpiIsSet; }
void LcsPrivacyData::unsetLpi() { m_LpiIsSet = false; }
UnrelatedClass LcsPrivacyData::getUnrelatedClass() const {
  return m_UnrelatedClass;
}
void LcsPrivacyData::setUnrelatedClass(UnrelatedClass const &value) {
  m_UnrelatedClass = value;
  m_UnrelatedClassIsSet = true;
}
bool LcsPrivacyData::unrelatedClassIsSet() const {
  return m_UnrelatedClassIsSet;
}
void LcsPrivacyData::unsetUnrelatedClass() { m_UnrelatedClassIsSet = false; }
std::vector<PlmnOperatorClass> &LcsPrivacyData::getPlmnOperatorClasses() {
  return m_PlmnOperatorClasses;
}
void LcsPrivacyData::setPlmnOperatorClasses(
    std::vector<PlmnOperatorClass> const &value) {
  m_PlmnOperatorClasses = value;
  m_PlmnOperatorClassesIsSet = true;
}
bool LcsPrivacyData::plmnOperatorClassesIsSet() const {
  return m_PlmnOperatorClassesIsSet;
}
void LcsPrivacyData::unsetPlmnOperatorClasses() {
  m_PlmnOperatorClassesIsSet = false;
}

} // namespace oai::udr::model