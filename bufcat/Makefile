# Created by PaulChristmas
# 31.03.15

# Compiler
CC=gcc

# Program name
NAME=bufcat

all: $(NAME)

$(NAME): $(NAME).o libbufio
	$(CC) -o $@ $< -Wl,-rpath,../lib -L../lib -lbufio
$(NAME).o:
	$(CC) -o $@ -c -I../lib -ggdb $(NAME).c 

libbufio:
	$(MAKE) -C ../lib

clean:
	rm -f $(NAME) $(NAME).o
	$(MAKE) -C ../lib clean
