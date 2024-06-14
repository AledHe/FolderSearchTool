# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -I./include

# Source and build directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Target executable
TARGET := $(BIN_DIR)/searchfolder

# Find all source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Create a list of object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	@mkdir $(BIN_DIR) 2> nul || echo "Directory already exists"
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir $(OBJ_DIR) 2> nul || echo "Directory already exists"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up build files
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJDIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BINDIR)

# Phony targets
.PHONY: all clean
