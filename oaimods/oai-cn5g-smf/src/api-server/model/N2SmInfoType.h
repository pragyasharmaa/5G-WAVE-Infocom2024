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
 * N2SmInfoType.h
 *
 * Possible values are - PDU_RES_SETUP_REQ - PDU_RES_SETUP_RSP -
 * PDU_RES_SETUP_FAIL - PDU_RES_REL_CMD - PDU_RES_REL_RSP - PDU_RES_MOD_REQ -
 * PDU_RES_MOD_RSP - PDU_RES_MOD_FAIL - PDU_RES_NTY - PDU_RES_NTY_REL -
 * PDU_RES_MOD_IND - PDU_RES_MOD_CFM - PATH_SWITCH_REQ - PATH_SWITCH_SETUP_FAIL
 * - PATH_SWITCH_REQ_ACK - PATH_SWITCH_REQ_FAIL - HANDOVER_REQUIRED -
 * HANDOVER_CMD - HANDOVER_PREP_FAIL - HANDOVER_REQ_ACK -
 * HANDOVER_RES_ALLOC_FAIL - SECONDARY_RAT_USAGE
 */

#ifndef N2SmInfoType_H_
#define N2SmInfoType_H_

#include <nlohmann/json.hpp>

namespace oai {
namespace smf_server {
namespace model {

/// <summary>
/// Possible values are - PDU_RES_SETUP_REQ - PDU_RES_SETUP_RSP -
/// PDU_RES_SETUP_FAIL - PDU_RES_REL_CMD - PDU_RES_REL_RSP - PDU_RES_MOD_REQ -
/// PDU_RES_MOD_RSP - PDU_RES_MOD_FAIL - PDU_RES_NTY - PDU_RES_NTY_REL -
/// PDU_RES_MOD_IND - PDU_RES_MOD_CFM - PATH_SWITCH_REQ - PATH_SWITCH_SETUP_FAIL
/// - PATH_SWITCH_REQ_ACK - PATH_SWITCH_REQ_FAIL - HANDOVER_REQUIRED -
/// HANDOVER_CMD - HANDOVER_PREP_FAIL - HANDOVER_REQ_ACK -
/// HANDOVER_RES_ALLOC_FAIL - SECONDARY_RAT_USAGE
/// </summary>
class N2SmInfoType {
 public:
  N2SmInfoType();
  virtual ~N2SmInfoType();

  void validate();

  /////////////////////////////////////////////
  /// N2SmInfoType members

  friend void to_json(nlohmann::json& j, const N2SmInfoType& o);
  friend void from_json(const nlohmann::json& j, N2SmInfoType& o);

 protected:
};

}  // namespace model
}  // namespace smf_server
}  // namespace oai

#endif /* N2SmInfoType_H_ */
