# Client Server program using UNIX Domain Sockets

## Step 1: Compile the current project

Assuming that you are at the top of the workspace.

```
cd code/day-1/client-server-over-udp/src
ls
```

You will notice that the project has the following folders:

1. build
   1. This is where we are going to initiate the build from. All object files will be stored here.
1. include
   1. This is the top level include folder.
1. utils
   1. This is a top level convenience library that provides routines common to both server and client

Lets generate the files required to build.

```
cd build
./bootstrap.sh
```

This uses the auto-tools (Autoconf/Automake) to create Makefiles.

Lets build
```
make
```

At this point, the project completed building. We now have the utils library built.

## Step 2: Let us add a basic server

Copy over the code for a [basic server](code/day-1/client-server-over-udp/reserve/basic-server).

```
cd ..
mkdir server
cp -r reserve/basic-server/* server/
```

Change configure.ac to include the new Makefile.am

```
AC_CONFIG_FILES([Makefile
    utils/Makefile
    server/Makefile
    server/csuds-server/Makefile
    server/csudsd/Makefile
])
```

Change top level Makefile.am to include server after utils.

```
SUBDIRS = \
    utils \
    server
```

bootstrap and build

```
cd build
./bootstrap.sh
make
```

Run the server and make sure it works.

```
./server/csudsd/csudsd
echo $?
```

## Step 3: Let us add a basic client

Copy over the code for a [basic client](code/day-1/client-server-over-udp/reserve/basic-client).

```
cd ..
mkdir client
cp -r reserve/basic-client/* client/
```

Change configure.ac to include the new Makefile.am

```
AC_CONFIG_FILES([Makefile
    client/Makefile
    server/Makefile
    server/csuds-server/Makefile
    server/csudsd/Makefile
    utils/Makefile
])
```

Change top level Makefile.am to include server after utils.

```
SUBDIRS = \
    utils \
    server \
    client
```

bootstrap and build

```
cd build
./bootstrap.sh
make
```

## Step 4: Let us add a basic command line interface

Copy over the code for a [basic tools](code/day-1/client-server-over-udp/reserve/basic-tools).

```
cd ..
cp -r reserve/basic-tools/* .
```

Change configure.ac to include the new Makefile.am

```
AC_CONFIG_FILES([Makefile
    client/Makefile
    server/Makefile
    server/csuds-server/Makefile
    server/csudsd/Makefile
    tools/Makefile
    tools/csuds-cli/Makefile
    utils/Makefile
])
```

Change top level Makefile.am to include tools after client.

```
SUBDIRS = \
    utils \
    server \
    client \
    tools
```

bootstrap and build

```
cd build
./bootstrap.sh
make
```

Run the command line interface and ensure it works

```
./tools/csuds-cli/csuds-cli
echo $?
```

## Step 5: Let us define a UNIX Domain Socket and a listener for the server

Copy over the code for a [basic tools](code/day-1/client-server-over-udp/reserve/server-listener-with-epoll/csuds-server).

```
cd ../server/csuds-server
cp -r ../../../reserve/server-listener-with-epoll/csuds-server/*.[ch]* .
mkdir ../include
cp -r ../../../reserve/server-listener-with-epoll/include/* ../include
```

Change Makefile.am to include the new files.

```
libcsuds_server_la_SOURCES = \
    context.c \
    globals.c \
    libmain.c \
    listener.c \
    poller.c
```

The csuds-server folder builds a shared library. The corresponding header for
this library is csuds-server.h which is present in the include folder outside
the source folder.

We need to add a compile flag to support the compilation within the csuds-server
folder finding its public header. So, we add the path -I$(top_srcdir)/server/include
as shown below.

```
libcsuds_server_la_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir)/include/public \
    -I$(top_srcdir)/server/include
```
