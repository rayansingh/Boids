# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lSDL2

TARGET = boids
SRCS = main.cpp screen.cpp boid.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile .cpp files into .o files
%.o: %.pp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Clean the project (remove object files and executable)
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
