all: prog

prog: main.o clientes.o gestores.o veiculos.o reservas.o historico.o grafo.o
	gcc -g -o prog main.o clientes.o gestores.o veiculos.o reservas.o historico.o grafo.o

main.o: main.c structs.h help.h
	gcc -g -o main.o main.c -c

clientes.o: clientes.c structs.h help.h
	gcc -g -o clientes.o clientes.c -c

gestores.o: gestores.c structs.h help.h
	gcc -g -o gestores.o gestores.c -c

veiculos.o: veiculos.c structs.h help.h
	gcc -g -o veiculos.o veiculos.c -c

reservas.o: reservas.c structs.h help.h
	gcc -g -o reservas.o reservas.c -c

historico.o: historico.c structs.h help.h
	gcc -g -o historico.o historico.c -c

grafo.o: grafo.c structs.h help.h
	gcc -g -o grafo.o grafo.c -c


clean:
	del /Q /S *.o *~ math

run:
	MinGW32-make clean
	MinGW32-make all
	./prog