#pragma once

#include <optional>
#include <string>

class Storage {
public:
    virtual ~Storage() = default;

    virtual bool set(
        const std::string& key,
        const std::string& value,
        int ttl_seconds = -1
    ) = 0;

    virtual std::optional<std::string> get(
        const std::string& key
    ) = 0;

    virtual bool remove(
        const std::string& key
    ) = 0;

    virtual bool exists(
        const std::string& key
    ) = 0;

    virtual void clear() = 0;
};