#include "api/server.h"

#include "rate_limiter/token_bucket.h"
#include "storage/redis_store.h"
#include <cstdlib>
#include <memory>

int main() {
    const char* redis_host =
        std::getenv("REDIS_HOST");

    if (!redis_host) {
        redis_host = "localhost";
    }

    auto store =
        std::make_shared<RedisStore>(
            redis_host,
            6379
        );

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