/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_ENDPOINTS_BRAVE_POST_WALLETS_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_ENDPOINTS_BRAVE_POST_WALLETS_H_

#include <optional>
#include <string>
#include <vector>

#include "brave/components/brave_rewards/core/engine/endpoints/request_builder.h"
#include "brave/components/brave_rewards/core/engine/endpoints/response_handler.h"
#include "brave/components/brave_rewards/core/engine/endpoints/result_for.h"
#include "brave/components/brave_rewards/core/mojom/rewards.mojom.h"
#include "brave/components/brave_rewards/core/mojom/rewards_engine_internal.mojom.h"

// POST /v4/wallets
//
// Request body:
// {
//   "geo_country": "US"
// }
//
// clang-format off
// Response body:
// {
//   "paymentId": "33fe956b-ed15-515b-bccd-b6cc63a80e0e"
// }
// clang-format on

namespace brave_rewards::internal {
class RewardsEngine;

namespace endpoints {

class PostWallets;

template <>
struct ResultFor<PostWallets> {
  using Value = std::string;  // Rewards payment ID
  using Error = mojom::PostWalletsError;
};

class PostWallets final : public RequestBuilder,
                          public ResponseHandler<PostWallets> {
 public:
  static Result ProcessResponse(RewardsEngine& engine,
                                const mojom::UrlResponse&);

  PostWallets(RewardsEngine& engine, std::optional<std::string>&& geo_country);
  ~PostWallets() override;

 private:
  const char* Path() const;

  std::optional<std::string> Url() const override;
  std::optional<std::vector<std::string>> Headers(
      const std::string& content) const override;
  std::optional<std::string> Content() const override;
  std::string ContentType() const override;

  std::optional<std::string> geo_country_;
};

}  // namespace endpoints
}  // namespace brave_rewards::internal

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_ENDPOINTS_BRAVE_POST_WALLETS_H_
