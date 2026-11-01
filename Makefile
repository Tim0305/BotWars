# Source, header and build directories
BIN_DIR = bin
SRC_DIR = src
INC_DIR = include

# Compiler and flags: C++17 with project headers
CXX = g++
CXXFLAGS = -std=c++17 -I$(INC_DIR)

# Get all source files and their object filenames
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Executable path
TARGET = $(BIN_DIR)/main

# Build the application
all: $(TARGET)

$(OBJS): | $(BIN_DIR)

# Link all object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each .cpp file into an object file
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory when needed
$(BIN_DIR):
	mkdir $(BIN_DIR)

# Remove files inside bin; the build directory itself is retained
clean:
	rm bin/*
