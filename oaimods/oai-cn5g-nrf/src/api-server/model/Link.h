/**
 * NRF NFManagement Service
 * NRF NFManagement Service. © 2019, 3GPP Organizational Partners (ARIB, ATIS,
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
 * Link.h
 *
 *
 */

#ifndef Link_H_
#define Link_H_

#include <string>
#include <nlohmann/json.hpp>

namespace oai {
namespace nrf {
namespace model {

/// <summary>
///
/// </summary>
class Link {
 public:
  Link();
  virtual ~Link();

  void validate();

  /////////////////////////////////////////////
  /// Link members

  /// <summary>
  ///
  /// </summary>
  std::string getHref() const;
  void setHref(std::string const& value);
  bool hrefIsSet() const;
  void unsetHref();

  friend void to_json(nlohmann::json& j, const Link& o);
  friend void from_json(const nlohmann::json& j, Link& o);

 protected:
  std::string m_Href;
  bool m_HrefIsSet;
};

}  // namespace model
}  // namespace nrf
}  // namespace oai

#endif /* Link_H_ */
