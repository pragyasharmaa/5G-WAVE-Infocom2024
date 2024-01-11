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

#include "ApplicationDataSubs.h"

namespace oai::udr::model {

ApplicationDataSubs::ApplicationDataSubs() {
  m_NotificationUri = "";
  m_DataFiltersIsSet = false;
  m_Expiry = "";
  m_ExpiryIsSet = false;
  m_SupportedFeatures = "";
  m_SupportedFeaturesIsSet = false;
}

ApplicationDataSubs::~ApplicationDataSubs() {}

void ApplicationDataSubs::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json &j, const ApplicationDataSubs &o) {
  j = nlohmann::json();
  j["notificationUri"] = o.m_NotificationUri;
  if (o.dataFiltersIsSet() || !o.m_DataFilters.empty())
    j["dataFilters"] = o.m_DataFilters;
  if (o.expiryIsSet())
    j["expiry"] = o.m_Expiry;
  if (o.supportedFeaturesIsSet())
    j["supportedFeatures"] = o.m_SupportedFeatures;
}

void from_json(const nlohmann::json &j, ApplicationDataSubs &o) {
  j.at("notificationUri").get_to(o.m_NotificationUri);
  if (j.find("dataFilters") != j.end()) {
    j.at("dataFilters").get_to(o.m_DataFilters);
    o.m_DataFiltersIsSet = true;
  }
  if (j.find("expiry") != j.end()) {
    j.at("expiry").get_to(o.m_Expiry);
    o.m_ExpiryIsSet = true;
  }
  if (j.find("supportedFeatures") != j.end()) {
    j.at("supportedFeatures").get_to(o.m_SupportedFeatures);
    o.m_SupportedFeaturesIsSet = true;
  }
}

std::string ApplicationDataSubs::getNotificationUri() const {
  return m_NotificationUri;
}
void ApplicationDataSubs::setNotificationUri(std::string const &value) {
  m_NotificationUri = value;
}
std::vector<DataFilter> &ApplicationDataSubs::getDataFilters() {
  return m_DataFilters;
}
void ApplicationDataSubs::setDataFilters(std::vector<DataFilter> const &value) {
  m_DataFilters = value;
  m_DataFiltersIsSet = true;
}
bool ApplicationDataSubs::dataFiltersIsSet() const {
  return m_DataFiltersIsSet;
}
void ApplicationDataSubs::unsetDataFilters() { m_DataFiltersIsSet = false; }
std::string ApplicationDataSubs::getExpiry() const { return m_Expiry; }
void ApplicationDataSubs::setExpiry(std::string const &value) {
  m_Expiry = value;
  m_ExpiryIsSet = true;
}
bool ApplicationDataSubs::expiryIsSet() const { return m_ExpiryIsSet; }
void ApplicationDataSubs::unsetExpiry() { m_ExpiryIsSet = false; }
std::string ApplicationDataSubs::getSupportedFeatures() const {
  return m_SupportedFeatures;
}
void ApplicationDataSubs::setSupportedFeatures(std::string const &value) {
  m_SupportedFeatures = value;
  m_SupportedFeaturesIsSet = true;
}
bool ApplicationDataSubs::supportedFeaturesIsSet() const {
  return m_SupportedFeaturesIsSet;
}
void ApplicationDataSubs::unsetSupportedFeatures() {
  m_SupportedFeaturesIsSet = false;
}

} // namespace oai::udr::model
