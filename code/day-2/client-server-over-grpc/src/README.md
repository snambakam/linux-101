# csgrpc

This is a sample service that illustrates gRPC over Unix Domain Sockets

## How to build

### Bootstrap

```
cd build
./bootstrap.sh
```

### Build

Depends on: Bootstrap

```
cd build
make
```

### Package

Depends on: Build

```
cd build
make package
```

### Clean

Depends on: Bootstrap

To clean built objects.

```
cd build
make clean
```

To remove stage directories and files created by autoconf tooling

```
cd build
make distclean
```
