# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Files
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/program

# Targets
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(EXEC)
