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
 * ChangeItem.h
 *
 *
 */

#ifndef ChangeItem_H_
#define ChangeItem_H_

#include <string>

#include "ChangeType.h"
//#include "AnyType.h"
#include <nlohmann/json.hpp>

namespace oai::udr::model {

/// <summary>
///
/// </summary>
class ChangeItem {
public:
  ChangeItem();
  virtual ~ChangeItem();

  void validate();

  /////////////////////////////////////////////
  /// ChangeItem members

  /// <summary>
  ///
  /// </summary>
  ChangeType getOp() const;
  void setOp(ChangeType const &value);
  /// <summary>
  ///
  /// </summary>
  std::string getPath() const;
  void setPath(std::string const &value);
  /// <summary>
  ///
  /// </summary>
  std::string getFrom() const;
  void setFrom(std::string const &value);
  bool fromIsSet() const;
  void unsetFrom();
  /// <summary>
  ///
  /// </summary>
  //    AnyType getOrigValue() const;
  //    void setOrigValue(AnyType const& value);
  bool origValueIsSet() const;
  void unsetOrigValue();
  /// <summary>
  ///
  /// </summary>
  //    AnyType getNewValue() const;
  //    void setNewValue(AnyType const& value);
  bool newValueIsSet() const;
  void unsetNewValue();

  friend void to_json(nlohmann::json &j, const ChangeItem &o);
  friend void from_json(const nlohmann::json &j, ChangeItem &o);

protected:
  ChangeType m_Op;

  std::string m_Path;

  std::string m_From;
  bool m_FromIsSet;
  //    AnyType m_OrigValue;
  bool m_OrigValueIsSet;
  //    AnyType m_NewValue;
  bool m_NewValueIsSet;
};

} // namespace oai::udr::model

#endif /* ChangeItem_H_ */
