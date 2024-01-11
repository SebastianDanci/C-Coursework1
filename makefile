# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -g -std=c++17 -Iinclude

# Source files
SOURCES = $(wildcard src/*.cpp)

# Object files
OBJECTS = $(SOURCES:src/%.cpp=bin/%.o)

# Executable name
EXECUTABLE = bin/library

.PHONY: all clean

# Default make
all: $(EXECUTABLE)
	@echo "Library compiled."

# Linking the executable from the object files
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Compiling source files to object files
bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creating the bin directory if it doesn't exist
$(OBJECTS): | bin

bin:
	mkdir -p bin

# Cleaning up the build
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -rf bin
