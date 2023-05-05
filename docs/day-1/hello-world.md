# Hello World Program

## Step 1: Create a file - helloworld.c

1. Create a folder "hello-world" using mkdir
1. Create an empty file "hello-world.c" using touch

```
mkdir hello-world
cd hello-world
touch hello-world.c
```

Fill in the following content into hello-world.c

```
#include <stdio.h>

int main() {
    printf("Hello World\n");
    return 0;
}
```

### Step 2: Compile

```
gcc -o hello-world hello-world.c
```

### Step 3: Execute the program

```
./hello-world
```

### Step 5: Create a Makefile

```

all: hello-world

hello-world: hello-world.o
    gcc -o $@ $<

%.o: %.c
    gcc -c -o $@ $<

clean:
    @rm -f *.o
    @rm -f hello-world

```

#### Variation of the Makefile with potentially multiple sources

```

SRCS = \
    hello-world.c

OBJS=${SRCS:.c=.o}

all: hello-world

hello-world: $(OBJS)
    gcc -o $@ $<

%.o: %.c
    gcc -c -o $@ $<

clean:
    @rm -f $(OBJS)
    @rm -f hello-world

```

#### Variation of the Makefile with CFLAGS

```

CFLAGS=-Wall =ggdb

SRCS = \
    hello-world.c

OBJS=${SRCS:.c=.o}

all: hello-world

hello-world: $(OBJS)
    gcc -o $@ $<

%.o: %.c
    gcc $(CFLAGS) -c -o $@ $<

clean:
    @rm -f $(OBJS)
    @rm -f hello-world

```

# References

1. [Makefile reference](https://www.gnu.org/software/make/manual/)