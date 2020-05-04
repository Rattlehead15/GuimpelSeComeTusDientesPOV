ARGS = -g -Wall -Wextra -Werror -std=c99
CC = gcc
all: Ordenar.exe Generar.exe
clean: 
	rm *.o
	rm *.exe
Ordenar.exe: Ordenar.o Persona.o GList.o
	$(CC) $(ARGS) -o Ordenar.exe Ordenar.o Persona.o GList.o
Ordenar.o: Ordenar.c
	$(CC) $(ARGS) -c Ordenar.c
Persona.o: Persona.c Persona.h
	$(CC) $(ARGS) -c Persona.c
GList.o: GList.c GList.h
	$(CC) $(ARGS) -c GList.c
Generar.exe: Generar.o Persona.o
	$(CC) $(ARGS) Generar.o Persona.o -o Generar.exe
Generar.o: Generar.c
	$(CC) $(ARGS) -c Generar.c