all: prog

prog: main.o add.o
	gcc -g -o prog main.o add.o

main.o: main.c structs.h
	gcc -g -o main.o main.c -c

add.o: add.c structs.h
	gcc -g -o add.o add.c -c


clean:
	del /Q /S *.o *~ math

run:
	MinGW32-make clean
	MinGW32-make all
	./prog