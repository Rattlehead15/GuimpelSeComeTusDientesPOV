#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GList.h"
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

        glist_swap_datos(lista, min);
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
                glist_sacar(lista);
                glist_insertar_despues(j, lista);
                yaCambio = 1;
            } else if (j->prev == NULL && lista->prev != NULL) {
                glist_sacar(lista);
                glist_insertar_antes(j, lista);
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
        izq->next->prev = izq;
        return izq;
    } else {
        der->next = merge(izq, der->next, comp);
        der->next->prev = der;
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

int comparar_por_edad(void *p1, void *p2) {
    int a = ((Persona*)p1)->edad;
    int b = ((Persona*)p2)->edad;
    return a < b ? -1 : a == b ? 0 : 1;
}

int comparar_por_largo_de_pais(void *p1, void *p2) {
    int a = strlen(((Persona*)p1)->lugarDeNacimiento);
    int b = strlen(((Persona*)p2)->lugarDeNacimiento);
}

void probar_algoritmo(FILE* salida, GList lista, GList (*algoritmo) (GList, Compara), char *nombreAlg, Compara comparacion, char *nombreComp) {
    GList copia = glist_copiar(lista);
    clock_t inicio = clock();
    copia = algoritmo(copia, comparacion);
    clock_t fin = clock();
    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    fprintf(salida, "Prueba con el algoritmo: %s.\nComparando por: %s\nTiempo total: %f\n\n", nombreAlg, nombreComp, tiempo);
    glist_escribir_en_archivo(salida, copia, persona_escribir_void);
    glist_destruir_y_no_datos(copia);
}

int main(int argc, char **argv) {
    FILE *entrada = fopen(argc > 1 ? argv[1] : "dataset.txt", "r");
    GList lista = glist_leer_personas_de_archivo(entrada, persona_leer_de_archivo_void);
    fclose(entrada);

    FILE *salida = fopen("salida.txt", "w");

    probar_algoritmo(salida, lista,
    insertion_sort, "insertion sort",
    comparar_por_edad, "edad");

    probar_algoritmo(salida, lista,
    selection_sort, "selection sort",
    comparar_por_edad, "edad");

    probar_algoritmo(salida, lista,
    merge_sort, "merge sort",
    comparar_por_edad, "edad");

/*    probar_algoritmo(salida, lista,
    insertion_sort, "insertion sort",
    comparar_por_largo_de_pais, "largo del pais");

    probar_algoritmo(salida, lista,
    selection_sort, "selection sort",
    comparar_por_largo_de_pais, "largo del pais");

    probar_algoritmo(salida, lista,
    merge_sort, "merge sort",
    comparar_por_largo_de_pais, "largo del pais");*/

    glist_destruir(lista, persona_destruir_void);
    fclose(salida);
    return 0;
}
