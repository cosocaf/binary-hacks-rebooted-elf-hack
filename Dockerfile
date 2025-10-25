FROM --platform=linux/amd64 ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
  apt-get install -y --no-install-recommends \
    build-essential \
    gdb \
    gdb-server \
    ca-certificates \
    curl \
    git \
    vim && \
  rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

RUN gcc --version && gdb --version

CMD ["/bin/bash"]

