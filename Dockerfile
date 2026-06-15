FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    libhiredis-dev \
    libasio-dev

WORKDIR /app

COPY . .

RUN cmake -S . -B build -G Ninja && \
    cmake --build build

EXPOSE 8080

CMD ["./build/scaleguard"]