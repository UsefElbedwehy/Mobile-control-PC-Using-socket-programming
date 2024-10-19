# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++14

# Source files
SRC = server.cpp commands.cpp main.cpp terminal.cpp serverBase.cpp

# Object files (auto-generated from .cpp files)
OBJ = $(SRC:.cpp=.o)

# Output executable
TARGET = server

# Default rule
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

# Optional rule to run the server
run: $(TARGET)
	./$(TARGET)
