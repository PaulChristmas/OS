# Created by PaulChristmas
# 10.03.15

# Compiler
CC=gcc

# Flags
CFLAGS=-Wall -fPIC
LIBRARY=helpers

all: lib$(LIBRARY).so

lib$(LIBRARY).so: $(LIBRARY).o
	$(CC) -o $@ -shared $<

$(LIBRARY).o:
	$(CC) -o $@ -c $(CFLAGS) $(LIBRARY).c

clean:
	rm -f lib$(LIBRARY).so $(LIBRARY).o
