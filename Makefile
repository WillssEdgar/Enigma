
# Define the program name
PROG = enigma

# Compiler to be used
CC = gcc

# Uncomment the following lines if using GTK+ for GUI
# CFLAGS = `pkg-config --cflags gtk+-3.0`
# LIBS = `pkg-config --libs gtk+-3.0`

# Source files
SRCS = enigma.c reflector.c plugBoard.c rotor.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Dependency files (one per source file)
DEPS = $(SRCS:.c=.d)

# Compilation flags
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Default target
all: $(PROG)

# Linking the program
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LIBS)

# Rule to compile source files into object files and generate dependencies
%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean up build files
clean:
	rm -f $(PROG) $(OBJS) $(DEPS)

# Phony targets
.PHONY: all clean

