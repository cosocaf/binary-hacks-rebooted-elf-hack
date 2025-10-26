FROM --platform=linux/amd64 ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    software-properties-common \
    build-essential \
    gcc-14 g++-14 \
    gdb \
    patchelf \
    ca-certificates \
    curl \
    git \
    vim && \
    rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100 && \
    gcc --version && g++ --version

WORKDIR /workspace

RUN gcc --version && gdb --version

CMD ["/bin/bash"]

