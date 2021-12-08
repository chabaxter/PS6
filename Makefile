CC = g++
CFLAGS = -std=c++20 -c -g -Og -Wall -Werror -pedantic
OBJ = TextWriter.o RandWriter.o
DEPS = TextWriter.cpp RandWriter.cpp RandWriter.h
LIBS = 
EXE = TextWriter

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
