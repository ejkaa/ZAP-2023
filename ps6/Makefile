# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wno-vla-parameter
LDLIBS=-lm -lcurses
OUTPUT=ps6

# source files
SRC=$(wildcard *.c)

# object files
OBJ=$(SRC:.c=.o)

# targets
all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(OUTPUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# remove compiled files
clean:
	rm -rf $(OUTPUT) $(OBJ)