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
 * BatteryIndicationRm.h
 *
 *
 */

#ifndef BatteryIndicationRm_H_
#define BatteryIndicationRm_H_

#include <nlohmann/json.hpp>

#include "BatteryIndication.h"
#include "NullValue.h"

namespace oai::udr::model {

/// <summary>
///
/// </summary>
class BatteryIndicationRm {
public:
  BatteryIndicationRm();
  virtual ~BatteryIndicationRm();

  void validate();

  /////////////////////////////////////////////
  /// BatteryIndicationRm members

  /// <summary>
  ///
  /// </summary>
  bool isBatteryInd() const;
  void setBatteryInd(bool const value);
  bool batteryIndIsSet() const;
  void unsetBatteryInd();
  /// <summary>
  ///
  /// </summary>
  bool isReplaceableInd() const;
  void setReplaceableInd(bool const value);
  bool replaceableIndIsSet() const;
  void unsetReplaceableInd();
  /// <summary>
  ///
  /// </summary>
  bool isRechargeableInd() const;
  void setRechargeableInd(bool const value);
  bool rechargeableIndIsSet() const;
  void unsetRechargeableInd();

  friend void to_json(nlohmann::json &j, const BatteryIndicationRm &o);
  friend void from_json(const nlohmann::json &j, BatteryIndicationRm &o);

protected:
  bool m_BatteryInd;
  bool m_BatteryIndIsSet;
  bool m_ReplaceableInd;
  bool m_ReplaceableIndIsSet;
  bool m_RechargeableInd;
  bool m_RechargeableIndIsSet;
};

} // namespace oai::udr::model

#endif /* BatteryIndicationRm_H_ */
