CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = 
SRC_DIR = src
INC_DIR = include

# Define the source files
SRCS = $(SRC_DIR)/llist.c main.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the output executable
TARGET = main

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile the source files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean up object files and the target
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean

