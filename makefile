# Makefile for warship project

# Compiler
CC = g++ -std=c++17

# Compiler flags
CFLAGS = -Wall -g 

# Executable name
TARGET = warship

# Source files
SRCS = $(wildcard *.c)

# Object files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the executable
run: $(TARGET)
	./$(TARGET)  g++ -std=c++17

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean