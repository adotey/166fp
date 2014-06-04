CFLAGS = -std=c99 -Wall
CC = gcc

OBJECTS = rbtree.o rbdriver.o

rbdriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o rbdriver $(OBJECTS)

clean:
	rm -f rbdriver $(OBJECTS) *~

rbtree.o: rbtree.c rbtree.h
rbdriver.o: rbdriver.c