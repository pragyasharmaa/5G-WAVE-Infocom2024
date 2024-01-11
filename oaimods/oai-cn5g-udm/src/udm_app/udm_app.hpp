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

/*! \file udm_app.hpp
 \brief
 \author  Tien-Thinh NGUYEN
 \company Eurecom
 \date 2020
 \email: Tien-Thinh.Nguyen@eurecom.fr
 */

#ifndef FILE_UDM_APP_HPP_SEEN
#define FILE_UDM_APP_HPP_SEEN

#include <string>
#include "AuthenticationInfoRequest.h"
#include "PlmnId.h"
#include "Amf3GppAccessRegistration.h"
#include "Snssai.h"
#include "PlmnId.h"
#include "SdmSubscription.h"
#include <pistache/http.h>
#include <map>
#include <shared_mutex>
#include "AuthEvent.h"

namespace oai {
namespace udm {
namespace app {

// class ausf_config;
class udm_app {
 public:
  explicit udm_app(const std::string& config_file);
  udm_app(udm_app const&) = delete;
  void operator=(udm_app const&) = delete;

  virtual ~udm_app();
  void handle_generate_auth_data_request(
      const std::string& supiOrSuci,
      const oai::udm::model::AuthenticationInfoRequest&
          authenticationInfoRequest,
      nlohmann::json& auth_info_response, Pistache::Http::Code& code);

  void handle_confirm_auth(
      const std::string& supi, const oai::udm::model::AuthEvent& authEvent,
      nlohmann::json& confirm_response, std::string& location,
      Pistache::Http::Code& code);

  void handle_delete_auth(
      const std::string& supi, const std::string& authEventId,
      const oai::udm::model::AuthEvent& authEvent,
      nlohmann::json& auth_response, Pistache::Http::Code& code);

  void handle_access_mobility_subscription_data_retrieval(
      const std::string& supi, nlohmann::json& response_data,
      Pistache::Http::Code& code, oai::udm::model::PlmnId PlmnId = {});

  void handle_amf_registration_for_3gpp_access(
      const std::string& ue_id,
      const oai::udm::model::Amf3GppAccessRegistration&
          amf_3gpp_access_registration,
      nlohmann::json& response_data, Pistache::Http::Code& code);

  void handle_session_management_subscription_data_retrieval(
      const std::string& supi, nlohmann::json& response_data,
      Pistache::Http::Code& code, oai::udm::model::Snssai snssai = {},
      std::string dnn = {}, oai::udm::model::PlmnId plmn_id = {});

  void handle_slice_selection_subscription_data_retrieval(
      const std::string& supi, nlohmann::json& response_data,
      Pistache::Http::Code& code, std::string supported_features = {},
      oai::udm::model::PlmnId plmn_id = {});

  void handle_smf_selection_subscription_data_retrieval(
      const std::string& supi, nlohmann::json& response_data,
      Pistache::Http::Code& code, std::string supported_features = {},
      oai::udm::model::PlmnId plmn_id = {});

  void handle_subscription_creation(
      const std::string& supi,
      const oai::udm::model::SdmSubscription& sdmSubscription,
      nlohmann::json& response_data, Pistache::Http::Code& code);

 private:
};
}  // namespace app
}  // namespace udm
}  // namespace oai
#include "udm_config.hpp"

#endif /* FILE_UDM_APP_HPP_SEEN */
