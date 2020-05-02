#ifndef GLIST
#define GLIST

typedef struct _GNodo {
    void* dato;
    struct _GNodo* next;
    struct _GNodo* prev;
} GNodo;

typedef GNodo* GList;

void GList_destruirNodoConPersona(GList nodo);
#endif