/**
 * Nsmf_PDUSession
 * SMF PDU Session Service. © 2019, 3GPP Organizational Partners (ARIB, ATIS,
 * CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.1.0.alpha-1
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */
/*
 * GNbId.h
 *
 *
 */

#ifndef GNbId_H_
#define GNbId_H_

#include <string>
#include <nlohmann/json.hpp>

namespace oai {
namespace smf_server {
namespace model {

/// <summary>
///
/// </summary>
class GNbId {
 public:
  GNbId();
  virtual ~GNbId();

  void validate();

  /////////////////////////////////////////////
  /// GNbId members

  /// <summary>
  ///
  /// </summary>
  int32_t getBitLength() const;
  void setBitLength(int32_t const value);
  /// <summary>
  ///
  /// </summary>
  std::string getGNBValue() const;
  void setGNBValue(std::string const& value);

  friend void to_json(nlohmann::json& j, const GNbId& o);
  friend void from_json(const nlohmann::json& j, GNbId& o);

 protected:
  int32_t m_BitLength;

  std::string m_GNBValue;
};

}  // namespace model
}  // namespace smf_server
}  // namespace oai

#endif /* GNbId_H_ */
