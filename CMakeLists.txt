cmake_minimum_required(VERSION 3.20)

project(ScaleGuard VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_library(storage
    src/storage/memory_store.cpp
)

target_include_directories(storage PUBLIC include)

add_executable(test_storage
    tests/test_storage.cpp
)

target_link_libraries(test_storage PRIVATE storage)