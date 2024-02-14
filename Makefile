# Makefile for this program

# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g

# Source files
SRCS = $(wildcard *.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Executable
TARGET = main

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	rm -f $(OBJS)
# Rule to clean up generated files
clean:
	rm -f $(TARGET)
