# Game Boy Emulator Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
LDFLAGS = -lSDL2

# Source directories
SRC_DIRS = src/core src/cpu src/memory src/ppu
OBJ_DIR = obj

# Source files
SRCS = $(shell find $(SRC_DIRS) -name '*.c')
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Executable name
TARGET = gbe

# Default target
all: $(TARGET)

# Create object directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/src/core
	mkdir -p $(OBJ_DIR)/src/cpu
	mkdir -p $(OBJ_DIR)/src/memory
	mkdir -p $(OBJ_DIR)/src/ppu

# Compile source files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(TARGET): $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run the emulator
run: $(TARGET)
	./$(TARGET) $(ROM)

.PHONY: all clean run