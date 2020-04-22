#include <stdio.h>
#include <stdlib.h>

#define acceder(nodo, tipo) (*(tipo*) (nodo->dato)) 

typedef struct _Nodo {
    void* dato;
    struct _Nodo* next;
} Nodo;

typedef Nodo* Lista;

typedef struct {
char * nombre ;
int edad ;
char * lugarDeNacimiento ; // pais o capital
} Persona ;

// if (i < personasALeer) { // Al principio, se llena el array de personas con las primeras n personas
//       personas[i] = nueva;
//     } else {
//       int j = rand() % (i + 1);  // Luego, para cada linea, se genera un número al azar j entre 1 y i, siendo i la linea actual
//       if (j < personasALeer) { // Si el numero j es menor que n, se reemplaza el j-esimo elemento del array por el elemento de la linea leida
//         personas[j] = nueva; // Esto nos asegura que las personas son elegidas de manera aleatoria con la misma frecuencia sin importar el tamano de la entrada
//       } else {
//         free(buff); // Si esta persona no va a entrar al array, se libera la memoria que le correspondía
//       }
// }

int main(int argc, char **argv)
{
    FILE *nombresFile = fopen("nombres1.txt", "r");
    FILE *paisesFile = fopen("paises.txt", "r");
    int cantPersonas = argc > 1 ? atoi(argv[1]) : 200;
    Persona *personas = (Persona*) malloc(sizeof(Persona) * cantPersonas);
    int cantPaises = 0;
    char buff;
    while ((buff = fgetc(paisesFile)) != EOF)
    {
        if (buff == '\n') {
            cantPaises++;
        }
    }
    char **paises = (char**) malloc(sizeof(char*) * cantPaises);
    for (int i = 0; i < cantPaises; i++)
        paises[i] = (char*) malloc(sizeof(char) * 100);

    rewind(paisesFile);

    for(int i = 0; fscanf(paisesFile, "%[^\n]\n", paises[i]) != EOF; i++){}
    return 0;
}