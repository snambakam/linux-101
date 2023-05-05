# Client Server Program over Unix Domain Sockets

## Requirements

### Server

1. The server program is an executable.
1. The server program should open a UNIX domain socket and listen for incoming connections.
   1. The UNIX domain socket must be at /var/lib/msft/csudpd.
1. The server program should accept connections from clients whose uid or egid is 0.
1. The server program should support the namespace "version" and the verb "get".
   1. The version is of the format major.minor.release where major, minor and release are positive integers.
1. The server must be multi-threaded
   1. The server should use a separate thread to fulfill each incoming client request

### Client

1. The client program is a shared library
1. The client program should provide a header
1. The client library should provide a method that returns the version
1. The client library should communicate with the server using the UNIX Domain Socket


### Command line program

1. The command line program is an executable
1. The command line program should dynamically link with the client library
1. The command line program should provide the means to retrieve the version from the server

