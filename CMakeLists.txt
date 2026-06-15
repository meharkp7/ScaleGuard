cmake_minimum_required(VERSION 3.20)

project(ScaleGuard VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(HIREDIS_LIB hiredis REQUIRED)

include_directories(include /opt/homebrew/include)

add_library(storage
    src/storage/memory_store.cpp
    src/storage/redis_store.cpp
    src/rate_limiter/token_bucket.cpp
)

target_include_directories(storage PUBLIC include)

target_link_libraries(storage PUBLIC ${HIREDIS_LIB})

add_executable(test_storage
    tests/test_storage.cpp
)

target_link_libraries(test_storage PRIVATE storage)

add_executable(test_redis
    tests/test_redis_store.cpp
)

target_link_libraries(test_redis PRIVATE storage)

add_executable(test_token_bucket
    tests/test_token_bucket.cpp
    src/rate_limiter/token_bucket.cpp
)

target_link_libraries(
    test_token_bucket
    PRIVATE
    storage
)