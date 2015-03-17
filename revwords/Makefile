# Created by PaulChristmas
# 15.03.15

# Compiler
CC=gcc

# Program name
NAME=revwords

all: $(NAME)

$(NAME): $(NAME).o libhelpers
	$(CC) -o $@ $< -Wl,-rpath,../lib -L../lib -lhelpers 
$(NAME).o:
	$(CC) -o $@ -c -I../lib -ggdb $(NAME).c 

libhelpers:
	$(MAKE) -C ../lib

clean:
	rm -f $(NAME) $(NAME).o
	$(MAKE) -C ../lib clean
