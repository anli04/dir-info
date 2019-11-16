ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.c
	gcc main.c

run:
	./a.out

memcheck:
	valgrind --leak-check=yes ./a.out

clean:
	rm *.o
	rm *~
