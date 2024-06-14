FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    qt6-base-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /3d_viewer/src

COPY . /3d_viewer/src

RUN make install
