#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Glist.h"
#include "Persona.h"

typedef int (* Compara ) ( void * dato1 , void * dato2 );

GList selection_sort(GList lista, Compara comp) {
    GList l = lista;

    for (; lista != NULL; lista=lista->next)
    {
        GList min = lista;
        for (GList j = lista; j != NULL; j=j->next)
        {
            if(comp(j->dato, min->dato) < 0) { 
                min = j;
            }
        }

        void* aux;
        aux = lista->dato;
        lista->dato = min->dato;
        min->dato = aux;
    }

    return l;
}

GList insertion_sort(GList lista, Compara comp) {
    GList principio = lista;
    GList sig = lista;
    for (; lista != NULL; lista=sig)
    {
        int yaCambio = 0;
        sig = lista->next;
        for (GList j = lista; j != NULL && !yaCambio; j=j->prev)
        {
            if(comp(j->dato, lista->dato) < 0) {
                if(lista->next != NULL) {
                    lista->next->prev = lista->prev;
                }
                lista->prev->next = lista->next;
                lista->prev = j;
                if(j->next != NULL) {
                    j->next->prev = lista;
                }
                lista->next = j->next;
                j->next = lista;

                yaCambio = 1;

            } else if (j->prev == NULL && lista->prev != NULL) {
                if(lista->next != NULL)
                    lista->next->prev = lista->prev;
                lista->prev->next = lista->next;
                j->prev = lista;
                lista->next = j;
                lista->prev = NULL;
                principio = lista;
                yaCambio = 1;
            }
        }
    }

    return principio;
}

GList merge(GList izq, GList der, Compara comp) {
    if (izq == NULL)
        return der;
    if (der == NULL) 
        return izq;

    if (comp(izq->dato, der->dato) < 0)
    {
        izq->next = merge(izq->next, der, comp);
        return izq;
    } else {
        der->next = merge(izq, der->next, comp);
        return der;
    }
}

GList merge_sort(GList lista, Compara comp) {
    GList izq = lista, der = lista;
    if(lista == NULL || lista->next == NULL)
        return lista;
    
    for(; lista!=NULL && lista->next != NULL; lista=lista->next->next) {
        der = der->next;
    }

    der->prev->next = NULL;
    der->prev = NULL;

    izq = merge_sort(izq, comp);
    der = merge_sort(der, comp);

    return merge(izq, der, comp);
}

int compararPorEdad(void *p1, void *p2) {
    int a = ((Persona*)p1)->edad;
    int b = ((Persona*)p2)->edad;
    return a < b ? -1 : a == b ? 0 : 1;
}

int main(int argc, char **argv) {
    FILE *entrada = fopen(argc > 1 ? argv[1] : "dataset.txt", "r");
    Persona *leido = (Persona*) malloc(sizeof(Persona));
    leido->nombre = (char*) malloc(sizeof(char) * 100);
    leido->lugarDeNacimiento = (char*) malloc(sizeof(char) * 100);
    GList leer = (GList) malloc(sizeof(GNodo));
    GList lista = leer;
    lista->prev = NULL;
    for (; fscanf(entrada, "%[^,], %d, %[^\n]\n", leido->nombre, &leido->edad, leido->lugarDeNacimiento) != EOF;)
    {
        leer->dato = leido;
        leer->next = (GList) malloc(sizeof(GNodo));
        leer->next->prev = leer;
        leer = leer->next;

        leido = (Persona*) malloc(sizeof(Persona));
        leido->nombre = (char*) malloc(sizeof(char) * 100);
    }
    GList_destruirNodoConPersona(leer);

    lista = merge_sort(lista, compararPorEdad);

    FILE *coso = fopen("salida.txt", "w");
    for (; lista != NULL; lista = lista->next)
    {
        Persona *pers = (Persona*) lista->dato;
        fprintf(coso, "%s %d %s\n", pers->nombre, pers->edad, pers->lugarDeNacimiento);
    }
    
    fclose(coso);
    return 0;
}