CC=g++
SOURCES=numerical_integration.cpp
OBJECTS=$(SOURCES)
EXECUTABLE=numerical_integration
CFLAGS=-Wall -lrt -fopenmp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

numerical_integration.o: numerical_integration.cpp
	$(CC) $(CFLAGS) $@

run:	all
	./numerical_integration -f input.dat
clean: 
	rm -rf *.o numerical_integration
