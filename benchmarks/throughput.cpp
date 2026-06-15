#include <chrono>
#include <future>
#include <iostream>
#include <vector>
#include <cstdlib>

void sendRequest() {
    system(
        "curl -s -X POST localhost:8080/allow "
        "-H \"Content-Type: application/json\" "
        "-d '{\"user_id\":\"benchmark\"}' > /dev/null"
    );
}

int main() {
    const int REQUESTS = 1000;

    auto start =
        std::chrono::high_resolution_clock::now();

    std::vector<std::future<void>> tasks;

    for (int i = 0; i < REQUESTS; i++) {
        tasks.push_back(
            std::async(
                std::launch::async,
                sendRequest
            )
        );
    }

    for (auto& task : tasks) {
        task.get();
    }

    auto end =
        std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<
            std::chrono::milliseconds
        >(end - start);

    std::cout
        << "Processed "
        << REQUESTS
        << " requests in "
        << duration.count()
        << " ms\n";

    return 0;
}