#include "rate_limiter/fixed_window.h"

FixedWindow::FixedWindow(
    int max_requests,
    int window_seconds,
    std::shared_ptr<Storage> storage
)
    : max_requests_(max_requests),
      window_seconds_(window_seconds),
      storage_(std::move(storage)) {}

bool FixedWindow::allowRequest(
    const std::string& user_id
) {
    std::lock_guard<std::mutex> lock(mutex_);

    std::string key =
        "window:" + user_id;

    int requests = 0;

    auto value =
        storage_->get(key);

    if (value.has_value()) {
        requests = std::stoi(
            value.value()
        );
    }

    if (requests >= max_requests_) {
        return false;
    }

    requests++;

    storage_->set(
        key,
        std::to_string(requests),
        window_seconds_
    );

    return true;
}