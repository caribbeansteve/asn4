OBJS = darray.o integer.o binomial.o sll.o queue.o
CC = gcc
FLAGS = gcc -Wall -g -std=c99 

dijkstra: $(OBJS)
	$(FLAGS) dijkstra.c -o dijkstra $(OBJS) -lm
binomial.o: binomial.c binomial.h
	$(FLAGS) -c binomial.c
integer.o: integer.c integer.h
	$(FLAGS) -c integer.c
darray.o: darray.c darray.h
	$(FLAGS) -c darray.c
queue.o: queue.c queue.h
	$(FLAGS) -c queue.c
sll.o: sll.c sll.h
	$(FLAGS) -c sll.c
clean:
	rm -f *.o
test:
	./dijkstra