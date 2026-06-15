#include <cassert>
#include <iostream>
#include <memory>

#include "rate_limiter/fixed_window.h"
#include "storage/memory_store.h"

int main() {
    auto store =
        std::make_shared<MemoryStore>();

    FixedWindow limiter(
        3,
        60,
        store
    );

    assert(
        limiter.allowRequest("mehar")
    );

    assert(
        limiter.allowRequest("mehar")
    );

    assert(
        limiter.allowRequest("mehar")
    );

    assert(
        !limiter.allowRequest("mehar")
    );

    std::cout
        << "Fixed window tests passed!\n";

    return 0;
}