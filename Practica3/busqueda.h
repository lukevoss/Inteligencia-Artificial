/*******************************************/
/* 		    BUSQUEDA.H                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include "puzle.h"

#ifndef _tNodo_
#define _tNodo_
typedef struct NodoBusqueda_{
    tEstado *estado;
    unsigned operador;
    int costeCamino;
    int profundidad;
    int valHeuristica;
    struct NodoBusqueda_ *padre;
} tNodo;

#endif

LISTA* find_node(LISTA* head, tEstado* estado_actual);

//Búsqueda en Anchura:
int busquedaAnchura(void);

//Búsqueda en Profundidad
int busquedaProfundidad(void);

//Búsqueda en Anchura:
int busquedaAnchurasinRep(void);

//Búsqueda en Profundidad
int busquedaProfundidadsinRep(void);

//Búsqueda en Profundidad Limitada
int busquedaProfundidadLimitada(int limite);

//Búsqueda Voraz
int busquedaVoraz();

void solucionFin(int res);
