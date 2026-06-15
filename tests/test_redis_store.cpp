#include <cassert>
#include <iostream>

#include "storage/redis_store.h"

int main() {
    RedisStore store;

    store.clear();

    assert(store.set("user1", "allowed", 60));

    auto value = store.get("user1");

    assert(value.has_value());
    assert(value.value() == "allowed");

    assert(store.exists("user1"));

    assert(store.remove("user1"));

    assert(!store.exists("user1"));

    std::cout << "Redis tests passed!\n";

    return 0;
}