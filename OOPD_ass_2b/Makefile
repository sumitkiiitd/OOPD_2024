# Compiler settings
CC := g++
DEBUG_FLAGS := -g -O0
OPTIMIZE_FLAGS := -O3
CFLAGS := -Wall

# Source files and output names
SRC := libraryn.cpp -lpthread
DEBUG_OUT := debug_library
OPTIMIZE_OUT := optimize_library

# Targets
all: debug optimize

debug: $(DEBUG_OUT)

optimize: $(OPTIMIZE_OUT)

$(DEBUG_OUT): $(SRC)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_OUT) $(SRC)

$(OPTIMIZE_OUT): $(SRC)
	$(CC) $(CFLAGS) $(OPTIMIZE_FLAGS) -o $(OPTIMIZE_OUT) $(SRC)

clean:
	rm -f $(DEBUG_OUT) $(OPTIMIZE_OUT)