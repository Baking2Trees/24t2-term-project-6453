# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -O2 -std=c++11

# Include the OpenSSL library
LDFLAGS = -lssl -lcrypto

# Target executable
TARGET = merkle

# Source files
SRCS = main.cpp sha256.cpp merkle.cpp comparison.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: clean