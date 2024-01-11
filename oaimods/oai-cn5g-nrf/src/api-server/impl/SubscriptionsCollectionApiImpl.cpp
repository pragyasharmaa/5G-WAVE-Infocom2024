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

#include "SubscriptionsCollectionApiImpl.h"
#include "3gpp_29.500.h"
#include "ProblemDetails.h"
#include "logger.hpp"
#include "nrf_app.hpp"
#include "nrf_config.hpp"

extern oai::nrf::app::nrf_config nrf_cfg;

namespace oai {
namespace nrf {
namespace api {

using namespace oai::nrf::model;
using namespace oai::nrf::app;

SubscriptionsCollectionApiImpl::SubscriptionsCollectionApiImpl(
    std::shared_ptr<Pistache::Rest::Router> rtr, nrf_app* nrf_app_inst,
    std::string address)
    : SubscriptionsCollectionApi(rtr),
      m_nrf_app(nrf_app_inst),
      m_address(address) {}

void SubscriptionsCollectionApiImpl::create_subscription(
    const SubscriptionData& subscriptionData,
    Pistache::Http::ResponseWriter& response) {
  Logger::nrf_sbi().info("Got a request to create a new subscription");

  int http_code                  = 0;
  ProblemDetails problem_details = {};
  std::string sub_id;
  nlohmann::json json_sub = {};
  to_json(json_sub, subscriptionData);
  Logger::nrf_sbi().debug("Subscription data %s", json_sub.dump().c_str());

  m_nrf_app->handle_create_subscription(
      subscriptionData, sub_id, http_code, 1, problem_details);

  nlohmann::json json_data = {};
  std::string content_type = "application/json";

  if (http_code != HTTP_STATUS_CODE_201_CREATED) {
    to_json(json_data, problem_details);
    content_type = "application/problem+json";
  } else {
    to_json(json_data, subscriptionData);
    json_data["subscriptionId"] = sub_id;
    // Location header
    response.headers().add<Pistache::Http::Header::Location>(
        m_address + base + nrf_cfg.sbi_api_version + "/subscriptions/" +
        sub_id);
  }

  // content type
  response.headers().add<Pistache::Http::Header::ContentType>(
      Pistache::Http::Mime::MediaType(content_type));
  response.send(Pistache::Http::Code(http_code), json_data.dump().c_str());
}

}  // namespace api
}  // namespace nrf
}  // namespace oai
