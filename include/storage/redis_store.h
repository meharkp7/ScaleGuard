#pragma once

#include "storage/storage.h"

#include <hiredis/hiredis.h>
#include <memory>
#include <shared_mutex>
#include <string>

class RedisStore final : public Storage {
private:
    redisContext* context_;
    mutable std::shared_mutex mutex_;

public:
    RedisStore(
        const std::string& host = "127.0.0.1",
        int port = 6379
    );

    ~RedisStore() override;

    bool set(
        const std::string& key,
        const std::string& value,
        int ttl_seconds = -1
    ) override;

    std::optional<std::string> get(
        const std::string& key
    ) override;

    bool remove(
        const std::string& key
    ) override;

    bool exists(
        const std::string& key
    ) override;

    void clear() override;
};