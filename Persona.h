#ifndef PERSONA
#define PERSONA
#include <stdio.h>

typedef struct {
    char *nombre;
    int edad;
    char *lugarDeNacimiento;
} Persona;

void persona_destruir(Persona *p);

void persona_destruir_void(void *p);

Persona* persona_crear();

void persona_escribir(FILE* archivo, Persona* p);

void persona_escribir_void(FILE* archivo, void* p);

void* persona_leer_de_archivo_void(FILE *archivo);

#endif