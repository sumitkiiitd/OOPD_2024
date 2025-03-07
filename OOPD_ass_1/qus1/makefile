# Compiler
CXX = g++

# Compiler flags for debugging and optimization
CXXFLAGS_DEBUG = -g -Wall -std=c++11
CXXFLAGS_OPT = -O2 -Wall -std=c++11

# Source files
SRCS = main.cpp RealEstateLTCG.cpp

# Header files
HEADERS = RealEstateLTCG.h

# Executable names
TARGET_DEBUG = realestate_ltcg_debug
TARGET_OPT = realestate_ltcg_opt

# Default target to build both versions
all: $(TARGET_DEBUG) $(TARGET_OPT)

# Build the debug version
$(TARGET_DEBUG): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS_DEBUG) -o $(TARGET_DEBUG) $(SRCS)

# Build the optimized version
$(TARGET_OPT): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS_OPT) -o $(TARGET_OPT) $(SRCS)

# Clean up generated files
clean:
	rm -f $(TARGET_DEBUG) $(TARGET_OPT)

# Phony targets to avoid conflicts with file names
.PHONY: all clean
