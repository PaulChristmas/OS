CC = gcc
CFLAGS = -Wall -I../lib
LDFLAGS = -L../lib -Wl,-rpath=../lib
LDLIBS = -lhelpers

RM = rm -f
TARGET = filter

SRCS = filter.c 
OBJS = $(SRCS:.c=.o) 

all: $(TARGET)

$(TARGET): $(OBJS)
 
clean:
	-$(RM) $(TARGET) $(OBJS)
