CFLAGS =
CC = g++

OBJECTS = Cord.o CordDriver.o CordAppendDriver.o CordInsertDriver.o CordFetchDriver.o

all: CordDriver CordAppendDriver CordInsertDriver CordFetchDriver

CordDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o CordDriver CordDriver.o Cord.o

CordAppendDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o CordAppendDriver CordAppendDriver.o Cord.o

CordInsertDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o CordInsertDriver CordInsertDriver.o Cord.o

CordFetchDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o CordFetchDriver CordFetchDriver.o Cord.o


clean:
	rm -f CordDriver CordAppendDriver *.o *~

Cord.o: Cord.cpp Cord.h
CordDriver.o: CordDriver.cpp
CordAppendDriver.o: CordAppendDriver.cpp
CordInsertDriver.o: CordInsertDriver.cpp
CordFetchDriver.o: CordFetchDriver.cpp
