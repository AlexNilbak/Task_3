answer: main.o functions.o Makefile
	gcc -o answer main.o functions.o

main.o: main.c fun.h
	gcc -c main.c

functions.o: functions.c fun.h
	gcc -c functions.c

clean:
	rm answer main.o functions.o
