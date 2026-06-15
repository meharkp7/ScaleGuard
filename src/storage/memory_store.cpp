#include "storage/memory_store.h"
#include <mutex>
#include <shared_mutex>

bool MemoryStore::set(
    const std::string& key,
    const std::string& value,
    int ttl_seconds
) {
    (void)ttl_seconds;

    std::unique_lock lock(mutex_);
    store_[key] = value;

    return true;
}

std::optional<std::string> MemoryStore::get(
    const std::string& key
) {
    std::shared_lock lock(mutex_);

    auto it = store_.find(key);

    if (it == store_.end()) {
        return std::nullopt;
    }

    return it->second;
}

bool MemoryStore::remove(
    const std::string& key
) {
    std::unique_lock lock(mutex_);

    return store_.erase(key) > 0;
}

bool MemoryStore::exists(
    const std::string& key
) {
    std::shared_lock lock(mutex_);

    return store_.find(key) != store_.end();
}

void MemoryStore::clear() {
    std::unique_lock lock(mutex_);

    store_.clear();
}