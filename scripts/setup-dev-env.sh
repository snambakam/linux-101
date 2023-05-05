#!/bin/bash

# Install packages required for development

sudo apt install \
    autoconf \
    automake \
    build-essential \
    cmake \
    gdb \
    libtool

curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh ./get-docker.sh

sudo usermod -aG docker `whoami`
