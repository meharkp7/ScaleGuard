# ScaleGuard 🚀
### Distributed Rate Limiting Service in C++ with Redis, Docker, and REST APIs

ScaleGuard is a production-grade distributed rate limiting system built in **C++20**. It implements industry-standard rate limiting algorithms using **Redis-backed state management**, exposes REST APIs via **Crow**, and is fully containerized using **Docker Compose**.

---

## ✨ Features

- Distributed rate limiting using Redis
- Token Bucket algorithm
- Fixed Window algorithm
- Thread-safe implementation using mutexes and atomics
- REST API built with Crow
- Metrics collection and monitoring
- Dockerized deployment
- Redis service discovery via Docker networking
- Benchmarking support
- Production-grade project structure

---

## 🏗️ Architecture

```text
                    Client
                       │
                HTTP Requests
                       │
               ScaleGuard API
                       │
         ┌─────────────┴─────────────┐
         │                           │
    Token Bucket               Fixed Window
         │                           │
         └─────────────┬─────────────┘
                       │
                Storage Abstraction
                       │
         ┌─────────────┴─────────────┐
         │                           │
      Memory Store             Redis Store
                       │
                     Redis
                       │
               Docker Network
```

---

## 🛠 Tech Stack

| Category | Technologies |
|----------|-------------|
| Language | C++20 |
| API Framework | Crow |
| Database | Redis |
| Containerization | Docker, Docker Compose |
| Build System | CMake, Ninja |
| Networking | Asio |
| Redis Client | hiredis |
| CI/CD | GitHub Actions |

---

## 📂 Project Structure

```text
ScaleGuard/
├── include/
│   ├── api/
│   ├── metrics/
│   ├── rate_limiter/
│   ├── storage/
│   └── utils/
│
├── src/
│   ├── api/
│   ├── metrics/
│   ├── rate_limiter/
│   ├── storage/
│   └── main.cpp
│
├── tests/
├── benchmarks/
├── scripts/
├── third_party/
├── Dockerfile
├── docker-compose.yml
└── CMakeLists.txt
```

---

## ⚙️ Supported Algorithms

### Token Bucket

- Allows burst traffic
- Refills tokens at a constant rate
- Commonly used in APIs and cloud systems

Configuration:

```cpp
capacity = 10
refill_rate = 1 token/sec
```

---

### Fixed Window

- Maintains request counts within fixed intervals
- Simple and efficient implementation

---

## 🔒 Concurrency & Thread Safety

ScaleGuard uses:

- `std::mutex`
- `std::shared_mutex`
- `std::lock_guard`
- `std::shared_lock`
- `std::atomic`

to ensure safe concurrent access to shared state.

---

## 🚀 Running Locally

### Prerequisites

- CMake ≥ 3.20
- Ninja
- Redis
- C++20 compiler

### Build

```bash
mkdir build
cd build

cmake -G Ninja ..
ninja
```

### Run

```bash
./scaleguard
```

---

## 🐳 Docker Deployment

### Start Services

```bash
docker compose up --build
```

ScaleGuard runs on:

```text
http://localhost:5001
```

---

## 📡 API Endpoints

### Health Check

```http
GET /health
```

Response:

```text
OK
```

---

### Check Rate Limit

```http
POST /allow
```

Request:

```json
{
    "user_id": "mehar"
}
```

Response:

```json
{
    "allowed": true
}
```

---

### Metrics

```http
GET /metrics
```

Response:

```json
{
    "allowed_requests": 10,
    "rejected_requests": 5
}
```

---

## 📊 Benchmarking

Run benchmark:

```bash
./build/benchmark_throughput
```

Example output:

```text
Processed 1000 requests in 8213 ms
```

---

## 🧪 Testing

Run tests:

```bash
./build/test_storage
./build/test_token_bucket
./build/test_fixed_window
./build/test_redis
```

---

## 🔄 CI/CD

GitHub Actions automatically:

- Builds the project
- Runs unit tests
- Validates pull requests

Workflow:

```text
.github/workflows/ci.yml
```

---

## 🎯 Key Engineering Concepts Demonstrated

- Distributed Systems
- Concurrency and Synchronization
- Object-Oriented Design
- Systems Programming
- Backend Engineering
- Docker Networking
- Service Discovery
- Observability and Metrics
- Redis-backed State Management

---

## 📈 Future Improvements

- Sliding Window Log algorithm
- Prometheus integration
- Grafana dashboards
- Redis Cluster support
- gRPC APIs
- Authentication and API keys

---

## 👨‍💻 Author

**Mehar Kapoor**

B.Tech ECE-AI, IGDTUW

Interested in Distributed Systems, AI Systems, and Production Engineering.

---