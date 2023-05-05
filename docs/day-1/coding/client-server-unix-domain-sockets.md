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


