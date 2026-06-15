#include "storage/redis_store.h"
#include <mutex>
#include <stdexcept>

RedisStore::RedisStore(
    const std::string& host,
    int port
) {
    context_ = redisConnect(host.c_str(), port);

    if (context_ == nullptr || context_->err) {
        throw std::runtime_error(
            "Failed to connect to Redis"
        );
    }
}

RedisStore::~RedisStore() {
    if (context_) {
        redisFree(context_);
    }
}

bool RedisStore::set(
    const std::string& key,
    const std::string& value,
    int ttl_seconds
) {
    std::unique_lock lock(mutex_);

    redisReply* reply = nullptr;

    if (ttl_seconds > 0) {
        reply = static_cast<redisReply*>(
            redisCommand(
                context_,
                "SETEX %s %d %s",
                key.c_str(),
                ttl_seconds,
                value.c_str()
            )
        );
    } else {
        reply = static_cast<redisReply*>(
            redisCommand(
                context_,
                "SET %s %s",
                key.c_str(),
                value.c_str()
            )
        );
    }

    if (!reply) {
        return false;
    }

    bool success = reply->type == REDIS_REPLY_STATUS;

    freeReplyObject(reply);

    return success;
}

std::optional<std::string> RedisStore::get(
    const std::string& key
) {
    std::shared_lock lock(mutex_);

    redisReply* reply = static_cast<redisReply*>(
        redisCommand(
            context_,
            "GET %s",
            key.c_str()
        )
    );

    if (!reply) {
        return std::nullopt;
    }

    if (reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        return std::nullopt;
    }

    if (reply->type != REDIS_REPLY_STRING) {
        freeReplyObject(reply);
        return std::nullopt;
    }

    std::string value(reply->str);

    freeReplyObject(reply);

    return value;
}

bool RedisStore::remove(
    const std::string& key
) {
    std::unique_lock lock(mutex_);

    redisReply* reply = static_cast<redisReply*>(
        redisCommand(
            context_,
            "DEL %s",
            key.c_str()
        )
    );

    if (!reply) {
        return false;
    }

    bool deleted =
        reply->type == REDIS_REPLY_INTEGER &&
        reply->integer > 0;

    freeReplyObject(reply);

    return deleted;
}

bool RedisStore::exists(
    const std::string& key
) {
    std::shared_lock lock(mutex_);

    redisReply* reply = static_cast<redisReply*>(
        redisCommand(
            context_,
            "EXISTS %s",
            key.c_str()
        )
    );

    if (!reply) {
        return false;
    }

    bool exists =
        reply->type == REDIS_REPLY_INTEGER &&
        reply->integer == 1;

    freeReplyObject(reply);

    return exists;
}

void RedisStore::clear() {
    std::unique_lock lock(mutex_);

    redisReply* reply = static_cast<redisReply*>(
        redisCommand(
            context_,
            "FLUSHDB"
        )
    );

    if (reply) {
        freeReplyObject(reply);
    }
}