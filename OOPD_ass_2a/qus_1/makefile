CXX = g++
CXXFLAGS = -Wall -std=c++17

DEBUG_FLAGS = -g
OPTIMIZE_FLAGS = -O2

SRC = main.cpp
TARGET = admin_system

all: debug optimized

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(TARGET)_debug

optimized:
	$(CXX) $(CXXFLAGS) $(OPTIMIZE_FLAGS) $(SRC) -o $(TARGET)_opt

clean:
	rm -f $(TARGET)_debug $(TARGET)_opt
