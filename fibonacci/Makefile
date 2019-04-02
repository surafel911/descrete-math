CC =  clang
CFLAGS = -m64 -Wall -Werror -std=c99
BINARY = fibonacci
LIBRARIES = -lm
SOURCES = src/main.c

ifeq ($(OS),Windows_NT)
 CC = gcc
 BINARY :=  $(strip $(BINARY)).exe
endif

all:
	$(CC) -g $(CFLAGS) $(LIBRARIES) $(SOURCES) -o bin/$(BINARY)
