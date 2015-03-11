# Created by PaulChristmas
# 10.03.15

# Compiler
CC=gcc

# Program name
NAME=cat

all: $(NAME)

$(NAME): $(NAME).o libhelpers
	$(CC) -o $@ -L../lib -lhelpers $<

$(NAME).o:
	$(CC) -o $@ -c -I../lib $(NAME).c

libhelpers:
	$(MAKE) -C ../lib

clean:
	rm -f *.o
	rm -f $(NAME)

$(NAME): $(NAME).c
	gcc -Wall -std=c99 -I../lib -Wl,-rpath=../lib -L../lib $(NAME).c -o $(NAME) -lhelpers
