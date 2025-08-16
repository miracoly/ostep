LIBS =

CFLAGS  = -std=c11
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

# Enable AddressSanitizer with: make ASAN=1
ifeq ($(ASAN),1)
CFLAGS += $(ASANFLAGS)
endif

# All C files and their corresponding .out programs
SRCS   := $(wildcard *.c)
PROGS  := $(SRCS:.c=.out)

.PHONY: all
all: $(PROGS)

%.out: %.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) $< -o $@ $(LIBS)

run: 8.out
	@echo "Running"
	@./8.out

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM
