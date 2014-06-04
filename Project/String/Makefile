CFLAGS =
CC = g++

OBJECTS = StringAppendDriver.o StringInsertDriver.o StringFetchDriver.o

all: StringAppendDriver StringInsertDriver StringFetchDriver

StringAppendDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o StringAppendDriver StringAppendDriver.o

StringInsertDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o StringInsertDriver StringInsertDriver.o

StringFetchDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o StringFetchDriver StringFetchDriver.o

clean:
	rm -f StringAppendDriver StringInsertDriver StringFetchDriver $(OBJECTS) *~

StringAppendDriver.o: StringAppendDriver.cpp
StringInsertDriver.o: StringInsertDriver.cpp
StringFetchDriver.o: StringFetchDriver.cpp