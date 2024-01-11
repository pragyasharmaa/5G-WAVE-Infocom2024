/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NGAP-IEs"
 * 	found in "asn.1/Information Element Definitions.asn1"
 * 	`asn1c -pdu=all -fcompound-names -fno-include-deps -findirect-choice
 * -gen-PER -D src`
 */

#ifndef _Ngap_AssociatedQosFlowItem_H_
#define _Ngap_AssociatedQosFlowItem_H_

#include <asn_application.h>

/* Including external dependencies */
#include "Ngap_QosFlowIdentifier.h"
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Ngap_AssociatedQosFlowItem__qosFlowMappingIndication {
  Ngap_AssociatedQosFlowItem__qosFlowMappingIndication_ul = 0,
  Ngap_AssociatedQosFlowItem__qosFlowMappingIndication_dl = 1
  /*
   * Enumeration is extensible
   */
} e_Ngap_AssociatedQosFlowItem__qosFlowMappingIndication;

/* Forward declarations */
struct Ngap_ProtocolExtensionContainer;

/* Ngap_AssociatedQosFlowItem */
typedef struct Ngap_AssociatedQosFlowItem {
  Ngap_QosFlowIdentifier_t qosFlowIdentifier;
  long* qosFlowMappingIndication;                        /* OPTIONAL */
  struct Ngap_ProtocolExtensionContainer* iE_Extensions; /* OPTIONAL */
  /*
   * This type is extensible,
   * possible extensions are below.
   */

  /* Context for parsing across buffer boundaries */
  asn_struct_ctx_t _asn_ctx;
} Ngap_AssociatedQosFlowItem_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_Ngap_qosFlowMappingIndication_3;
 * // (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_Ngap_AssociatedQosFlowItem;
extern asn_SEQUENCE_specifics_t asn_SPC_Ngap_AssociatedQosFlowItem_specs_1;
extern asn_TYPE_member_t asn_MBR_Ngap_AssociatedQosFlowItem_1[3];

#ifdef __cplusplus
}
#endif

#endif /* _Ngap_AssociatedQosFlowItem_H_ */
#include <asn_internal.h>
