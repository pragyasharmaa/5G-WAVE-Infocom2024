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
/*
 * AcsInfoRm.h
 *
 *
 */

#ifndef AcsInfoRm_H_
#define AcsInfoRm_H_

#include <nlohmann/json.hpp>
#include <string>

#include "AcsInfo.h"
#include "Ipv6Addr.h"
#include "NullValue.h"

namespace oai::udr::model {

/// <summary>
///
/// </summary>
class AcsInfoRm {
public:
  AcsInfoRm();
  virtual ~AcsInfoRm();

  void validate();

  /////////////////////////////////////////////
  /// AcsInfoRm members

  /// <summary>
  ///
  /// </summary>
  std::string getAcsUrl() const;
  void setAcsUrl(std::string const &value);
  bool acsUrlIsSet() const;
  void unsetAcsUrl();
  /// <summary>
  ///
  /// </summary>
  std::string getAcsIpv4Addr() const;
  void setAcsIpv4Addr(std::string const &value);
  bool acsIpv4AddrIsSet() const;
  void unsetAcsIpv4Addr();
  /// <summary>
  ///
  /// </summary>
  Ipv6Addr getAcsIpv6Addr() const;
  void setAcsIpv6Addr(Ipv6Addr const &value);
  bool acsIpv6AddrIsSet() const;
  void unsetAcsIpv6Addr();

  friend void to_json(nlohmann::json &j, const AcsInfoRm &o);
  friend void from_json(const nlohmann::json &j, AcsInfoRm &o);

protected:
  std::string m_AcsUrl;
  bool m_AcsUrlIsSet;
  std::string m_AcsIpv4Addr;
  bool m_AcsIpv4AddrIsSet;
  Ipv6Addr m_AcsIpv6Addr;
  bool m_AcsIpv6AddrIsSet;
};

} // namespace oai::udr::model

#endif /* AcsInfoRm_H_ */
