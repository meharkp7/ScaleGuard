#include <cassert>

#include "storage/memory_store.h"

int main() {
    MemoryStore store;

    assert(store.set("user1", "allowed"));

    auto value = store.get("user1");

    assert(value.has_value());
    assert(value.value() == "allowed");

    assert(store.exists("user1"));

    store.remove("user1");

    assert(!store.exists("user1"));

    return 0;
}