# Makefile for writer application

# Default compiler settings (native build)
CC := gcc
CFLAGS := -Wall -Wextra

# Cross-compilation support
ifdef CROSS_COMPILE
    CC := $(CROSS_COMPILE)gcc
endif

# Targets
TARGET := writer
OBJ := writer.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

# Help target to show usage
help:
	@echo "Usage:"
	@echo "  make             - Build native version"
	@echo "  make clean       - Remove built files"
	@echo "  make CROSS_COMPILE=aarch64-none-linux-gnu-  - Cross-compile for ARM64"
