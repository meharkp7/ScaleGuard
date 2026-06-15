#pragma once

#include "storage/storage.h"

#include <memory>
#include <mutex>
#include <string>

class FixedWindow {
private:
    int max_requests_;
    int window_seconds_;

    std::shared_ptr<Storage> storage_;

    mutable std::mutex mutex_;

public:
    FixedWindow(
        int max_requests,
        int window_seconds,
        std::shared_ptr<Storage> storage
    );

    bool allowRequest(
        const std::string& user_id
    );
};