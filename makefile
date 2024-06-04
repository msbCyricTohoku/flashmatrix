# Define the compiler and flags
CXX = g++
CXXFLAGS = -lcurses

# Define the target executable
TARGET = flashmatrix

# Define the source files
SRCS = main.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) -c $< -o $@

# Rule to clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

