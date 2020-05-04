#include <stdlib.h>
#include "GList.h"

void glist_destruir(GList inicio, Destructor destruir) {
    while(inicio->next != NULL) {
        destruir(inicio->dato);
        inicio = inicio->next;
        free(inicio->prev);
    }
    destruir(inicio->dato);
    free(inicio);
}

void glist_destruir_y_no_datos(GList inicio) {
    while(inicio->next != NULL) {
        inicio = inicio->next;
        free(inicio->prev);
    }
    free(inicio);
}

void glist_destruir_nodo(GList nodo, Destructor destruir) {
    if(nodo->prev != NULL) {
        nodo->prev->next = nodo->next;
    }
    if(nodo->next != NULL) {
        nodo->next->prev = nodo->prev;
    }
    destruir(nodo->dato);
    free(nodo);
}

void glist_destruir_nodo_y_no_dato(GList nodo) {
    if(nodo->prev != NULL) {
        nodo->prev->next = nodo->next;
    }
    if(nodo->next != NULL) {
        nodo->next->prev = nodo->prev;
    }
    free(nodo);
}

GList glist_agregar_final(GList final) {
    final->next = (GList) malloc(sizeof(GNodo));
    final->next->next = NULL;
    final->next->prev = final;
    return final->next;
}

GList glist_copiar(GList inicio) {
    GList nueva = (GList) malloc(sizeof(GNodo));
    nueva->prev = NULL;
    GList finalNueva = nueva;

    for (; inicio != NULL; inicio = inicio->next)
    {
        finalNueva->dato = inicio->dato;
        finalNueva = glist_agregar_final(finalNueva);
    }
    glist_destruir_nodo_y_no_dato(finalNueva);
    return nueva;
}

void glist_swap_datos(GList nodo1, GList nodo2) {
    void* aux;
    aux = nodo1->dato;
    nodo1->dato = nodo2->dato;
    nodo2->dato = aux;
}

GList glist_sacar(GList nodo) {
    if(nodo->prev != NULL) {
        nodo->prev->next = nodo->next;
    }
    if(nodo->next != NULL) {
        nodo->next->prev = nodo->prev;
    }

    nodo->prev = NULL;
    nodo->next = NULL;

    return nodo;
}

void glist_insertar_despues(GList lugar, GList nodoAInsertar) {
    nodoAInsertar->prev = lugar;
    nodoAInsertar->next = lugar->next;
    if(lugar->next != NULL) {
        lugar->next->prev = nodoAInsertar;
    }
    lugar->next = nodoAInsertar;
}

void glist_insertar_antes(GList lugar, GList nodoAInsertar) {
    nodoAInsertar->next = lugar;
    nodoAInsertar->prev = lugar->prev;
    if(lugar->prev != NULL) {
        lugar->prev->next = nodoAInsertar;
    }
    lugar->prev = nodoAInsertar;
}

GList glist_leer_personas_de_archivo(FILE *archivo, Lector leer) {
    GList lista = (GList) malloc(sizeof(GNodo));
    lista->prev = NULL;
    GList sig = lista;
    for (; (sig->dato = leer(archivo)) != NULL;)
    {
        sig = glist_agregar_final(sig);
    }
    glist_destruir_nodo_y_no_dato(sig);
    return lista;
}

void glist_escribir_en_archivo(FILE *archivo, GList inicio, Escritor escribir) {
    for (; inicio != NULL; inicio = inicio->next)
    {
        escribir(archivo, inicio->dato);
    }
    fputc('\n', archivo);
}