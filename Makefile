# Define compiler and compiler flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic

# Define source, object, and binary directories
SRCDIR := src
OBJDIR := obj
BINDIR := bin

# Define source and object files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Define the binary file
TARGET := $(BINDIR)/game

# Define phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create the binary file
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean up object and binary files
clean:
	rm -rf $(OBJDIR) $(BINDIR)
