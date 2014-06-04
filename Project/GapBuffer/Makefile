CFLAGS =
CC = g++

OBJECTS = GapBuffer.o GapBufferDriver.o GapBufferAppendDriver.o GapBufferInsertDriver.o GapBufferFetchDriver.o

all: GapBufferDriver GapBufferAppendDriver GapBufferInsertDriver GapBufferFetchDriver

GapBufferDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o GapBufferDriver GapBufferDriver.o GapBuffer.o

GapBufferAppendDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o GapBufferAppendDriver GapBufferAppendDriver.o GapBuffer.o

GapBufferInsertDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o GapBufferInsertDriver GapBufferInsertDriver.o GapBuffer.o

GapBufferFetchDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o GapBufferFetchDriver GapBufferFetchDriver.o GapBuffer.o

clean:
	rm -f GapBufferDriver GapBufferAppendDriver *.o *~

GapBuffer.o: GapBuffer.cpp GapBuffer.h
GapBufferDriver.o: GapBufferDriver.cpp
GapBufferAppendDriver.o: GapBufferAppendDriver.cpp
GapBufferInsertDriver.o: GapBufferInsertDriver.cpp
GapBufferFetchDriver.o: GapBufferFetchDriver.cpp
