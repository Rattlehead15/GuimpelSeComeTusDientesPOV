#include "GList.h"
#include "Persona.h"
#define acceder(nodo, tipo) (*(tipo*) (nodo->dato)) 

void GList_destruirNodoConPersona(GList nodo) {
    Persona p = acceder(nodo, Persona);
}