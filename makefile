CC=gcc
LIBS=-lncurses
CFLAGS=-g -Wall 
SOURCES=gameoflife.c
TARGET=game

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ -I /usr/include/ncurses -I /usr/include/ncursew $(LIBS) 

clean:
	rm -rf *.o
