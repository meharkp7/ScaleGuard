#include "api/server.h"
#include "metrics/metrics.h"
#include "crow/app.h"
#include "crow/json.h"

Server::Server(
    std::shared_ptr<TokenBucket> limiter
)
    : limiter_(std::move(limiter)) {}

void Server::start(int port) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/health")
    ([]() {
        return "OK";
    });

    CROW_ROUTE(app, "/allow")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req) {

        auto body =
            crow::json::load(req.body);

        if (!body) {
            return crow::response(
                400,
                "Invalid JSON"
            );
        }

        std::string user_id =
            body["user_id"].s();

        bool allowed =
            limiter_->allowRequest(
                user_id
            );

        crow::json::wvalue result;

        result["allowed"] =
            allowed;

        return crow::response(
            result
        );
    });

    CROW_ROUTE(app, "/metrics")
        ([]() {

            crow::json::wvalue result;

            result["allowed_requests"] =
                Metrics::allowed_requests.load();

            result["rejected_requests"] =
                Metrics::rejected_requests.load();

            return crow::response(result);
        });

    app.port(port)
       .multithreaded()
       .run();
}