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

#include "MbsfnArea.h"

namespace oai::udr::model {

MbsfnArea::MbsfnArea() {
  m_MbsfnAreaId = 0;
  m_MbsfnAreaIdIsSet = false;
  m_CarrierFrequency = 0;
  m_CarrierFrequencyIsSet = false;
}

MbsfnArea::~MbsfnArea() {}

void MbsfnArea::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json &j, const MbsfnArea &o) {
  j = nlohmann::json();
  if (o.mbsfnAreaIdIsSet())
    j["mbsfnAreaId"] = o.m_MbsfnAreaId;
  if (o.carrierFrequencyIsSet())
    j["carrierFrequency"] = o.m_CarrierFrequency;
}

void from_json(const nlohmann::json &j, MbsfnArea &o) {
  if (j.find("mbsfnAreaId") != j.end()) {
    j.at("mbsfnAreaId").get_to(o.m_MbsfnAreaId);
    o.m_MbsfnAreaIdIsSet = true;
  }
  if (j.find("carrierFrequency") != j.end()) {
    j.at("carrierFrequency").get_to(o.m_CarrierFrequency);
    o.m_CarrierFrequencyIsSet = true;
  }
}

int32_t MbsfnArea::getMbsfnAreaId() const { return m_MbsfnAreaId; }
void MbsfnArea::setMbsfnAreaId(int32_t const value) {
  m_MbsfnAreaId = value;
  m_MbsfnAreaIdIsSet = true;
}
bool MbsfnArea::mbsfnAreaIdIsSet() const { return m_MbsfnAreaIdIsSet; }
void MbsfnArea::unsetMbsfnAreaId() { m_MbsfnAreaIdIsSet = false; }
int32_t MbsfnArea::getCarrierFrequency() const { return m_CarrierFrequency; }
void MbsfnArea::setCarrierFrequency(int32_t const value) {
  m_CarrierFrequency = value;
  m_CarrierFrequencyIsSet = true;
}
bool MbsfnArea::carrierFrequencyIsSet() const {
  return m_CarrierFrequencyIsSet;
}
void MbsfnArea::unsetCarrierFrequency() { m_CarrierFrequencyIsSet = false; }

} // namespace oai::udr::model
