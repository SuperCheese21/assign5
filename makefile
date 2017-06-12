CC=gcc
exe1=run_compiler
exe2=run_queue

all: $(exe1) $(exe2)
$(exe1): compiler.o list.o
	$(CC) compiler.o list.o -o $(exe1)
$(exe2): run_queue.o test_queue.o list.o
	$(CC) run_queue.o test_queue.o list.o -o $(exe2)
compiler.o: compiler.c
	$(CC) -c compiler.c
run_queue.o: run_queue.c
	$(CC) -c run_queue.c
test_queue.o: test_queue.c
	$(CC) -c test_queue.c
list.o: list.c
	$(CC) -c list.c
clean:
	rm -f *.out *.o $(exe1) $(exe2)
