#include "api/server.h"

#include "rate_limiter/token_bucket.h"
#include "storage/redis_store.h"

#include <memory>

int main() {
    auto store =
        std::make_shared<RedisStore>();

    auto limiter =
        std::make_shared<TokenBucket>(
            10,
            1.0,
            store
        );

    Server server(limiter);

    server.start(8080);

    return 0;
}