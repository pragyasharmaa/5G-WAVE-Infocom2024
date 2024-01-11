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

#include "InfluenceDataStoreApi.h"

#include "Helpers.h"
#include "udr_config.hpp"

extern oai::udr::config::udr_config udr_cfg;

namespace oai::udr::api {

using namespace oai::udr::helpers;
using namespace oai::udr::model;

InfluenceDataStoreApi::InfluenceDataStoreApi(
    std::shared_ptr<Pistache::Rest::Router> rtr) {
  router = rtr;
}

void InfluenceDataStoreApi::init() { setupRoutes(); }

void InfluenceDataStoreApi::setupRoutes() {
  using namespace Pistache::Rest;

  Routes::Get(
      *router,
      base + udr_cfg.nudr.api_version + "/application-data/influenceData",
      Routes::bind(&InfluenceDataStoreApi::read_influence_data_handler, this));

  // Default handler, called when a route is not found
  router->addCustomHandler(Routes::bind(
      &InfluenceDataStoreApi::influence_data_store_api_default_handler, this));
}

void InfluenceDataStoreApi::read_influence_data_handler(
    const Pistache::Rest::Request &request,
    Pistache::Http::ResponseWriter response) {
  // Getting the query params
  auto influenceIdsQuery = request.query().get("influence-Ids");
  Pistache::Optional<std::vector<std::string>> influenceIds;
  if (!influenceIdsQuery.isEmpty()) {
    std::vector<std::string> valueQuery_instance;
    if (fromStringValue(influenceIdsQuery.get(), valueQuery_instance)) {
      influenceIds = Pistache::Some(valueQuery_instance);
    }
  }
  auto dnnsQuery = request.query().get("dnns");
  Pistache::Optional<std::vector<std::string>> dnns;
  if (!dnnsQuery.isEmpty()) {
    std::vector<std::string> valueQuery_instance;
    if (fromStringValue(dnnsQuery.get(), valueQuery_instance)) {
      dnns = Pistache::Some(valueQuery_instance);
    }
  }
  auto snssaisQuery = request.query().get("snssais");
  Pistache::Optional<std::vector<Snssai>> snssais;
  if (!snssaisQuery.isEmpty()) {
    //        std::vector<Snssai> valueQuery_instance;
    //        if(fromStringValue(snssaisQuery.get(), valueQuery_instance)){
    //            snssais = Pistache::Some(valueQuery_instance);
    //        }
  }
  auto internalGroupIdsQuery = request.query().get("internal-Group-Ids");
  Pistache::Optional<std::vector<std::string>> internalGroupIds;
  if (!internalGroupIdsQuery.isEmpty()) {
    std::vector<std::string> valueQuery_instance;
    if (fromStringValue(internalGroupIdsQuery.get(), valueQuery_instance)) {
      internalGroupIds = Pistache::Some(valueQuery_instance);
    }
  }
  auto supisQuery = request.query().get("supis");
  Pistache::Optional<std::vector<std::string>> supis;
  if (!supisQuery.isEmpty()) {
    std::vector<std::string> valueQuery_instance;
    if (fromStringValue(supisQuery.get(), valueQuery_instance)) {
      supis = Pistache::Some(valueQuery_instance);
    }
  }
  auto suppFeatQuery = request.query().get("supp-feat");
  Pistache::Optional<std::string> suppFeat;
  if (!suppFeatQuery.isEmpty()) {
    std::string valueQuery_instance;
    if (fromStringValue(suppFeatQuery.get(), valueQuery_instance)) {
      suppFeat = Pistache::Some(valueQuery_instance);
    }
  }

  try {
    this->read_influence_data(influenceIds, dnns, snssais, internalGroupIds,
                              supis, suppFeat, response);
  } catch (nlohmann::detail::exception &e) {
    // send a 400 error
    response.send(Pistache::Http::Code::Bad_Request, e.what());
    return;
  } catch (Pistache::Http::HttpError &e) {
    response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
    return;
  } catch (std::exception &e) {
    // send a 500 error
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
    return;
  }
}

void InfluenceDataStoreApi::influence_data_store_api_default_handler(
    const Pistache::Rest::Request &, Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Not_Found,
                "The requested method does not exist");
}

} // namespace oai::udr::api
