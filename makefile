# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++11 -Iinclude

# Source files
SOURCES = $(wildcard src/*.cpp)

# Object files
OBJECTS = $(SOURCES:src/%.cpp=bin/%.o)

# Executable name
EXECUTABLE = bin/library_system

.PHONY: all clean

# Default make
all: $(EXECUTABLE)
	@echo "Library system has been compiled."

# Linking the executable from the object files
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

# Compiling source files to object files
bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning up the build
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
