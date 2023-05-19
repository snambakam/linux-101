# Client Server using gRPC and UNIX Domain Sockets

## Preparation

### Mariner

```
sudo tdnf install -y \
    protobuf \
    grpc \
    grpc-plugins \
    grpc-devel \
    c-ares-devel \
    re2-devel \
    util-linux-devel
```

Note: We are using util-liinux-devel because it provides <uuid/uuid.h>

### Ubuntu

```
sudo apt install -y \
    protobuf-compiler-grpc \
    libprotobuf-dev \
    libgrpc-dev
```

## Step 1: Build bootstrap code

```
cd code/day-2/client-server-over-grpc
cd build
./bootstrap.sh
```

## Step 2: Implement Sample GrpC Server

```
cd ../server/csgrpcd
cp ../../../reserve/implement-grpc-server/* .
cd ../../build
make
```

## Step 3: Implement Sample GrpC Client

```
cd ../client/include
cp ../../../reserve/implement-grpc-client/include/* .
cd ../src
cp ../../../reserve/implement-grpc-client/src/* .
cd ../../build
make
```

## Step 4: Implement Sample GrpC Client Command Line Interface

```
cd ../tools/cli
cp ../../../reserve/implement-cli/* .
cd ../../build
make
```

## Step 5: Test Client/Server over gRPC

### Run server in a terminal

```
sudo ./server/csgrpcd/csgrpcd
```

### Run GrpC Client CLI in another terminal

```
sudo ./tools/cli/csgrpc-cli version
```
