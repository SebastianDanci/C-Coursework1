# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -g -std=c++17

# Include path
INCLUDE_PATH = -Iinclude

# Source files for the library (excluding main and test)
LIB_SOURCES = $(filter-out src/main.cpp src/test.cpp, $(wildcard src/*.cpp))

# Object files for the library
LIB_OBJECTS = $(LIB_SOURCES:src/%.cpp=bin/%.o)

# Main source file for the library
MAIN_SOURCE = src/main.cpp

# Main object file for the library
MAIN_OBJECT = bin/main.o

# Source files for the tests (excluding main and test)
TEST_SOURCES = $(filter-out src/main.cpp, $(wildcard tests/*.cpp))

# Object files for the tests
TEST_OBJECTS = $(TEST_SOURCES:tests/%.cpp=bin/%.o)

# Test object for Catch2's main
TEST_MAIN_OBJECT = bin/test.o

# Executable names
EXECUTABLE = bin/library
TEST_EXECUTABLE = bin/tester

.PHONY: all library test clean

# Default make
all: library test

# Rule to make the library
library: $(EXECUTABLE)

# Rule to make the tests
test: $(TEST_EXECUTABLE)

# Linking the library executable
$(EXECUTABLE): $(LIB_OBJECTS) $(MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) $^ -o $@

# Linking the test executable
$(TEST_EXECUTABLE): $(LIB_OBJECTS) $(TEST_OBJECTS) $(TEST_MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) $^ -o $@

# Compiling source files to object files
bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Compiling test files to object files
bin/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Creating the bin directory if it doesn't exist
$(LIB_OBJECTS) $(TEST_OBJECTS) $(MAIN_OBJECT) $(TEST_MAIN_OBJECT): | bin

bin:
	mkdir -p bin

# Cleaning up the build
clean:
	rm -f $(LIB_OBJECTS) $(TEST_OBJECTS) $(MAIN_OBJECT) $(TEST_MAIN_OBJECT) $(EXECUTABLE) $(TEST_EXECUTABLE)
	rm -rf bin
