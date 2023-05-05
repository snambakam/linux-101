# linux-101

## Introduction

This repository attempts to provide an introduction to Linux for developers who are already familiar with computer systems and programming in general. We will learn through Interprocess Communication on Linux using Unix Domain Sockets.

## Plan

### Day 1

1. Setup Development Environment
   1. Create the Host (Ubuntu VM on Azure)
   1. Setup SSH Connectivity
   1. Provision packages required for development
   1. Setup remote session on VSCode
1. Basic introduction to Linux
   1. Security 101
      1. Users, Groups
      1. PAM, NSSwitch
      1. Basic tools (whoami, id etc.)
    1. Networking 101
    1. Logging
    1. Process Management
    1. UNIX Shell(s)
    1. Some basic commands
1. Develop a Hello World Program using C
1. Introduction to GDB
1. Introduction to the UNIX process model
1. Introduction to POSIX threads
1. Introduction to Signals
1. Develop a multi-threaded client/server app using Unix Domain Sockets
   1. Basic introduction to auto-tools (Autoconf/Automake/Configure/Make)
   1. Develop the server
   1. Develop the client
   1. Develop the command line interface that links with the client

#### Exercises

1. Extend the Server to use syslog.
   1. Verify using journalctl.
1. Extend the Server to use a JSON based config file.
   1. Define a signal handler that responds to SIGUSR1 to refresh the config file.

### Day 2

1. Convert the service to gRPC
1. Introduction to CMake
   1. Convert the service to use CMake instead of auto-tools
1. Introduction to UNIX daemons
   1. Convert the serfvice to be a UNIX daemon
1. Introduction to Redhat Package Manager (RPM)
1. Build an RPM for the service

### Day 3

1. Introduction to systemd
1. Define the gRPC server as a systemd service
   1. Ensure the service is started automatically upon installation
   1. Ensure the service is automatically removed upon uninstallation
1. Debug the running service
1. Debug from core
1. Introduction to performance tools on Linux

# References

1. Resources on building infrastructure
   1. [Auto tools](https://www.sourceware.org/autobook/)
   1. [CMake](https://cmake.org/cmake/help/book/mastering-cmake/)
1. Training
   1. [Linux Foundation Training](https://training.linuxfoundation.org/full-catalog/)
1. Books
   1. Advanced Programming in the Linux Environment by Richard L. Stevens
   1. [UNIX Network Programming Volumes 1 & 2](https://archive.org/details/unix-network-programming/Unix%20Network%20Programming%20Vol%201%20W.%20Richard%20Stevens/)