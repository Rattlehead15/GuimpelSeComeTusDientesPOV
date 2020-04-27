#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define acceder(nodo, tipo) (*(tipo*) (nodo->dato)) 

typedef struct {
char nombre[100];
int edad;
char lugarDeNacimiento[100];
} Persona;

typedef struct _Nodo {
    void* dato;
    struct _Nodo* next;
    struct _Nodo* prev;
} Nodo;

typedef Nodo* Lista;

typedef int (* Compara ) ( void * dato1 , void * dato2 ) ;

void selection_sort(Lista lista, Compara comp) {
    for (; lista != NULL; lista=lista->next)
    {
        Lista min = lista;
        for (Lista j = lista; j != NULL; j=j->next)
        {
            if(comp(j->dato, min->dato)) { 
                min = j;
            }
        }

        void* aux;
        aux = lista->dato;
        lista->dato = min->dato;
        min->dato = aux;
    }
}

void insertion_sort(Lista lista, Compara comp) {
    for (; lista != NULL; lista=lista->next)
    {
        for (Lista j = lista; j != NULL; j=j->prev)
        {
            if(comp(j->dato, lista->dato) && lista->prev != NULL) {
                if(lista->next != NULL) {
                    lista->next->prev = lista->prev;
                }
                lista->prev->next = lista->next;
                lista->prev = j;
                j->next->prev = lista;
                lista->next = j->next;
                j->next = lista;

            } else if (j->prev == NULL && lista->prev != NULL) {
                if(lista->next != NULL)
                    lista->next->prev = lista->prev;
                lista->prev->next = lista->next;
                j->prev = lista;
                lista->next = j;
                lista->prev = NULL;
            }
        }
        
    }
}

Lista merge(Lista izq, Lista der, Compara comp) {
    if (izq == NULL)
        return der;
    if (der == NULL) 
        return izq;

    if (comp(izq->dato, der->dato))
    {
        izq->next = merge(izq->next, der, comp);
        return izq;
    } else {
        der->next = merge(izq, der->next, comp);
        return der;
    }
}

Lista merge_sort(Lista lista, Compara comp) {
    Lista izq = lista, der = lista;
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
    return ((Persona*)p1)->edad < ((Persona*)p2)->edad;
}

int main(int argc, char **argv) {
    FILE *entrada = fopen(argc > 1 ? argv[1] : "dataset.txt", "r");
    Persona *leido = (Persona*) malloc(sizeof(Persona));
    Lista leer = (Lista) malloc(sizeof(Nodo));
    Lista lista = leer;
    lista->prev = NULL;
    for (; fscanf(entrada, "%[^,], %d, %[^\n]\n", leido->nombre, &leido->edad, leido->lugarDeNacimiento) != EOF;)
    {
        leer->dato = leido;
        leer->next = (Lista) malloc(sizeof(Nodo));
        leer->next->prev = leer;
        leer = leer->next;

        leido = (Persona*) malloc(sizeof(Persona));
    }
    leer = leer->prev;
    free(leer->next);
    leer->next = NULL;

    insertion_sort(lista, compararPorEdad);


    return 0;
}