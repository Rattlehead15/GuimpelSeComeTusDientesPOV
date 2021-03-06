#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
char * nombre;
int edad;
char * lugarDeNacimiento;
} Persona;

#define PERSONAS_DEFAULT 200
#define BUFFER_DEFAULT 100

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
    int cantPersonas = argc > 1 ? atoi(argv[1]) : PERSONAS_DEFAULT;
    srand(argc > 2 ? atoi(argv[2]) : time(NULL));
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
        paises[i] = (char*) malloc(sizeof(char) * BUFFER_DEFAULT);

    rewind(paisesFile);

    for(int i = 0; fscanf(paisesFile, "%[^\n]\n", paises[i]) != EOF; i++){}

    char *nombre = (char*) malloc(sizeof(char) * BUFFER_DEFAULT);
    for (int i = 0; fscanf(nombresFile, "%[^\n]\n", nombre) != EOF; i++)
    {
        if (i < cantPersonas)
        {
            personas[i].nombre = nombre;
            personas[i].edad = (rand() % BUFFER_DEFAULT) + 1;
            personas[i].lugarDeNacimiento = paises[rand() % (cantPaises + 1)];
        } else {
            int r = rand() % (i + 1);
            if (r < cantPersonas)
            {
                free(personas[r].nombre);
                personas[r].nombre = nombre;
            } else {
                free(nombre);
            }
        }

        nombre = (char*) malloc(sizeof(char) * BUFFER_DEFAULT);
    }

    FILE *outputFile = fopen("dataset.txt", "w");
    for (int i = 0; i < cantPersonas; i++)
    {
        fprintf(outputFile, "%s, %d, %s\n", personas[i].nombre, personas[i].edad, personas[i].lugarDeNacimiento);
    }

    return 0;
}