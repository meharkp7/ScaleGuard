#include <cassert>
#include <iostream>
#include <memory>

#include "rate_limiter/token_bucket.h"
#include "storage/memory_store.h"

int main() {
    auto store =
        std::make_shared<MemoryStore>();

    TokenBucket bucket(
        3,
        1.0,
        store
    );

    assert(
        bucket.allowRequest("user")
    );

    assert(
        bucket.allowRequest("user")
    );

    assert(
        bucket.allowRequest("user")
    );

    assert(
        !bucket.allowRequest("user")
    );

    std::cout
        << "Token bucket tests passed!\n";

    return 0;
}