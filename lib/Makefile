# Created by PaulChristmas
# 10.03.15

# Compiler
CC=gcc

# Libraries, bufio added.
LIBH=helpers
LIBB=bufio

all: lib$(LIBB).so lib$(LIBH).so

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.out

lib$(LIBH).so: $(LIBH).o
	$(CC) -shared -o libhelpers.so helpers.o

$(LIBH).o: $(LIBH).c 
	$(CC) -c -std=c99 -fPIC -Wall -Werror helpers.c -o helpers.o 

lib$(LIBB).so: $(LIBB).o
	$(CC) -shared -o libbufio.so bufio.o

$(LIBB).o: $(LIBB).c
	$(CC) -c -std=c99 -fPIC -Wall -Werror bufio.c -o bufio.o 

