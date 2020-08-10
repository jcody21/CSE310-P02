EXEC = proj2
CC = g++
CFLAGS = -c -Wall

$(EXEC)	: main.o heap.o util.o graph.o
	$(CC) -o $(EXEC) main.o heap.o util.o graph.o

main.o	: main.cpp
	$(CC) $(CFLAGS) main.cpp

heap.o	: heap.h heap.cpp
	$(CC) $(CFLAGS) heap.cpp

util.o	: util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

graph.o : graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp

clean	:
	rm *.o