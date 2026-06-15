#pragma once

#include "storage/storage.h"

#include <optional>
#include <shared_mutex>
#include <string>
#include <unordered_map>

class MemoryStore final : public Storage {
private:
    std::unordered_map<std::string, std::string> store_;
    mutable std::shared_mutex mutex_;

public:
    MemoryStore() = default;
    ~MemoryStore() override = default;

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