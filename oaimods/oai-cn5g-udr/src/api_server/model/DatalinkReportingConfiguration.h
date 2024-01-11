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
 * DatalinkReportingConfiguration.h
 *
 *
 */

#ifndef DatalinkReportingConfiguration_H_
#define DatalinkReportingConfiguration_H_

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "DddTrafficDescriptor.h"
#include "DlDataDeliveryStatus.h"
#include "Snssai.h"

namespace oai::udr::model {

/// <summary>
///
/// </summary>
class DatalinkReportingConfiguration {
public:
  DatalinkReportingConfiguration();
  virtual ~DatalinkReportingConfiguration();

  void validate();

  /////////////////////////////////////////////
  /// DatalinkReportingConfiguration members

  /// <summary>
  ///
  /// </summary>
  std::vector<DddTrafficDescriptor> &getDddTrafficDes();
  void setDddTrafficDes(std::vector<DddTrafficDescriptor> const &value);
  bool dddTrafficDesIsSet() const;
  void unsetDddTrafficDes();
  /// <summary>
  ///
  /// </summary>
  std::string getDnn() const;
  void setDnn(std::string const &value);
  bool dnnIsSet() const;
  void unsetDnn();
  /// <summary>
  ///
  /// </summary>
  Snssai getSlice() const;
  void setSlice(Snssai const &value);
  bool sliceIsSet() const;
  void unsetSlice();
  /// <summary>
  ///
  /// </summary>
  std::vector<DlDataDeliveryStatus> &getDddStatusList();
  void setDddStatusList(std::vector<DlDataDeliveryStatus> const &value);
  bool dddStatusListIsSet() const;
  void unsetDddStatusList();

  friend void to_json(nlohmann::json &j,
                      const DatalinkReportingConfiguration &o);
  friend void from_json(const nlohmann::json &j,
                        DatalinkReportingConfiguration &o);

protected:
  std::vector<DddTrafficDescriptor> m_DddTrafficDes;
  bool m_DddTrafficDesIsSet;
  std::string m_Dnn;
  bool m_DnnIsSet;
  Snssai m_Slice;
  bool m_SliceIsSet;
  std::vector<DlDataDeliveryStatus> m_DddStatusList;
  bool m_DddStatusListIsSet;
};

} // namespace oai::udr::model

#endif /* DatalinkReportingConfiguration_H_ */
