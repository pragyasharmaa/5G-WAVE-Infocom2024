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
 * Nudm_SDM
 * Nudm Subscriber Data Management Service. � 2019, 3GPP Organizational Partners
 * (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 2.1.0.alpha-1
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "SubscriptionCreationApiImpl.h"

#include "udm_client.hpp"
#include "logger.hpp"
#include "udm_config.hpp"

extern oai::udm::config::udm_config udm_cfg;

namespace oai {
namespace udm {
namespace api {

using namespace oai::udm::model;
using namespace oai::udm::config;

SubscriptionCreationApiImpl::SubscriptionCreationApiImpl(
    std::shared_ptr<Pistache::Rest::Router> rtr, udm_app* udm_app_inst,
    std::string address)
    : SubscriptionCreationApi(rtr) {}

void SubscriptionCreationApiImpl::subscribe(
    const std::string& supi, const SdmSubscription& sdmSubscription,
    Pistache::Http::ResponseWriter& response) {
  nlohmann::json response_data = {};
  Pistache::Http::Code code    = {};

  m_udm_app->handle_subscription_creation(
      supi, sdmSubscription, response_data, code);

  // Set content type
  if ((code == Pistache::Http::Code::Created) or
      (code == Pistache::Http::Code::Accepted) or
      (code == Pistache::Http::Code::Ok) or
      (code == Pistache::Http::Code::No_Content)) {
    response.headers().add<Pistache::Http::Header::ContentType>(
        Pistache::Http::Mime::MediaType("application/json"));
  } else {
    response.headers().add<Pistache::Http::Header::ContentType>(
        Pistache::Http::Mime::MediaType("application/problem+json"));
  }

  response.send(code, response_data.dump().c_str());
}

}  // namespace api
}  // namespace udm
}  // namespace oai
