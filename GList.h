#ifndef GLIST
#define GLIST
#include <stdio.h>
#define GLIST_DATO(nodo, tipo) (*(tipo*) (nodo->dato))

typedef struct _GNodo {
    void* dato;
    struct _GNodo* next;
    struct _GNodo* prev;
} GNodo;

typedef GNodo* GList;

typedef void (*Destructor) (void*);

typedef void (*Escritor) (FILE*, void*);

typedef void* (*Lector) (FILE*);

void glist_destruir(GList inicio, Destructor destruir);

void glist_destruir_y_no_datos(GList inicio);

void glist_destruir_nodo(GList inicio, Destructor destruir);

void glist_destruir_nodo_y_no_dato(GList nodo);

GList glist_agregar_final(GList final);

GList glist_copiar(GList inicio);

void glist_swap_datos(GList nodo1, GList nodo2);

GList glist_sacar(GList nodo);

void glist_insertar_despues(GList lugar, GList nodoAInsertar);

void glist_insertar_antes(GList lugar, GList nodoAInsertar);

GList glist_leer_personas_de_archivo(FILE *archivo, Lector leer);

void glist_escribir_en_archivo(FILE *archivo, GList inicio, Escritor escribir);
#endif