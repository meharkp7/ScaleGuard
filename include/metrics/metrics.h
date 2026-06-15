#pragma once

#include <atomic>

class Metrics {
public:
    static inline std::atomic<long> allowed_requests{0};
    static inline std::atomic<long> rejected_requests{0};
};