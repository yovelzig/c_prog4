CC=gcc
FLAGS = -Wall -g

all: graph

graph: main.o 
	$(CC) $(FLAGS) main.o -o graph

main.o: main.c 
	$(CC) $(FLAGS) -c main.c 

.PHONY: clean 

clean:
	rm -f *.o *.a *.so graph


			