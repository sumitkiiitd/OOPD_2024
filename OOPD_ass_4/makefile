# Compiler and flags
CC := g++
CFLAGS := -Wall -Wextra -std=c++17
DEBUG_FLAGS := -g -O0
OPTIMIZED_FLAGS := -O3

# Source and binary files
SRC := main2.cpp
DEBUG_BINARY := publication_debug
OPTIMIZED_BINARY := publication_optimized

# Default target
.PHONY: all
all: $(DEBUG_BINARY) $(OPTIMIZED_BINARY)

# Debug build
$(DEBUG_BINARY): $(SRC)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

# Optimized build
$(OPTIMIZED_BINARY): $(SRC)
	$(CC) $(CFLAGS) $(OPTIMIZED_FLAGS) $^ -o $@

# Clean up generated files
.PHONY: clean
clean:
	rm -f $(DEBUG_BINARY) $(OPTIMIZED_BINARY)

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all        - Build both debug and optimized versions of the binary"
	@echo "  clean      - Remove generated binaries"
	@echo "  help       - Display this help message"
