#include "rate_limiter/token_bucket.h"

#include <algorithm>
#include <chrono>

TokenBucket::TokenBucket(
    int capacity,
    double refill_rate,
    std::shared_ptr<Storage> storage
)
    : capacity_(capacity),
      refill_rate_(refill_rate),
      storage_(std::move(storage)) {}

bool TokenBucket::allowRequest(
    const std::string& user_id
) {
    std::lock_guard<std::mutex> lock(mutex_);

    std::string token_key =
        "rate:" + user_id + ":tokens";

    std::string refill_key =
        "rate:" + user_id + ":last_refill";

    auto now =
        std::chrono::duration_cast<
            std::chrono::seconds
        >(
            std::chrono::system_clock::now()
                .time_since_epoch()
        ).count();

    int tokens = capacity_;
    long last_refill = now;

    auto stored_tokens =
        storage_->get(token_key);

    if (stored_tokens.has_value()) {
        tokens = std::stoi(
            stored_tokens.value()
        );
    }

    auto stored_refill =
        storage_->get(refill_key);

    if (stored_refill.has_value()) {
        last_refill = std::stol(
            stored_refill.value()
        );
    }

    long elapsed =
        now - last_refill;

    int new_tokens =
        static_cast<int>(
            elapsed * refill_rate_
        );

    tokens =
        std::min(
            capacity_,
            tokens + new_tokens
        );

    if (tokens < 1) {
        return false;
    }

    tokens--;

    storage_->set(
        token_key,
        std::to_string(tokens)
    );

    storage_->set(
        refill_key,
        std::to_string(now)
    );

    return true;
}