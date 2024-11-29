
CC = gcc
CFLAGS = -Wall -g
TARGET = main.o
SRC = shell.c builtins.c
OBJ = shell.o builtins.o


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

