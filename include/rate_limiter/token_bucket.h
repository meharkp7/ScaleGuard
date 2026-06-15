#pragma once

#include "storage/storage.h"

#include <memory>
#include <mutex>
#include <string>

class TokenBucket {
private:
    int capacity_;
    double refill_rate_;

    std::shared_ptr<Storage> storage_;

    mutable std::mutex mutex_;

public:
    TokenBucket(
        int capacity,
        double refill_rate,
        std::shared_ptr<Storage> storage
    );

    bool allowRequest(
        const std::string& user_id
    );
};