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

Lista selection_sort(Lista lista, Compara comp) {
    Lista l = lista;

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

    return l;
}

Lista insertion_sort(Lista lista, Compara comp) {
    Lista principio = lista;
    Lista sig = lista;
    for (; lista != NULL; lista=sig)
    {
        int yaCambio = 0;
        sig = lista->next;
        for (Lista j = lista; j != NULL && !yaCambio; j=j->prev)
        {
            if(comp(j->dato, lista->dato)) {
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