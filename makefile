all: Ordenar.exe Generar.exe
Ordenar.exe: Ordenar.o Persona.o GList.o
	gcc -g Ordenar.o Persona.o GList.o -o Ordenar.exe
Ordenar.o: Ordenar.c
	gcc -g -c Ordenar.c
Persona.o: Persona.c Persona.h
	gcc -g -c Persona.c
GList.o: GList.c GList.h
	gcc -g -c GList.c
Generar.exe: Generar.o Persona.o
	gcc -g Generar.o Persona.o -o Generar.exe
Generar.o: Generar.c
	gcc -g -c Generar.c