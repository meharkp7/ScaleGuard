#pragma once

#include "rate_limiter/token_bucket.h"

#include <memory>

class Server {
private:
    std::shared_ptr<TokenBucket> limiter_;

public:
    explicit Server(
        std::shared_ptr<TokenBucket> limiter
    );

    void start(int port = 8080);
};