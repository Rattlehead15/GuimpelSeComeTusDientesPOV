#include <stdlib.h>
#include "Persona.h"

void persona_destruir(Persona *p) {
    free(p->nombre);
    free(p->lugarDeNacimiento);
    free(p);
}

void persona_destruir_gente_y_no_pais(Persona *p, int cantPersonas) {
    for(int i = 0; i < cantPersonas; i++){
        free((p+i)->nombre);
    }
    free(p);
}

void persona_destruir_void(void *p) {
    persona_destruir((Persona*) p);
}

Persona* persona_crear() {
    Persona *nueva = (Persona*) malloc(sizeof(Persona));
    nueva->nombre = (char*) malloc(sizeof(char) * 100);
    nueva->lugarDeNacimiento = (char*) malloc(sizeof(char) * 100);
    return nueva;
}

void persona_escribir(FILE* archivo, Persona* p) {
    fprintf(archivo, "%s %d %s\n", p->nombre, p->edad, p->lugarDeNacimiento);
}

void persona_escribir_void(FILE* archivo, void* p) {
    persona_escribir(archivo, (Persona*) p);
}

void* persona_leer_de_archivo_void(FILE *archivo) {
    Persona* pers = persona_crear();
    if(fscanf(archivo, "%[^,], %d, %[^\n]\n", pers->nombre, &pers->edad, pers->lugarDeNacimiento) == EOF)
        return NULL;
    else return (void*) pers;
}
