# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -I/opt/homebrew/Cellar/boost/1.86.0_2/include

# Boost libraries
BOOST_LIBS = -L/opt/homebrew/Cellar/boost/1.86.0_2/lib -lboost_system -lboost_date_time

# Target executable
TARGET = task_scheduler

# Source files
SRCS = program1.cpp
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(BOOST_LIBS)

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
