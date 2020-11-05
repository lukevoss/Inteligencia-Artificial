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

//B�squeda en Anchura:
int busquedaAnchura(void);

//B�squeda en Profundidad
int busquedaProfundidad(void);

//B�squeda en Anchura:
int busquedaAnchurasinRep(void);

//B�squeda en Profundidad
int busquedaProfundidadsinRep(void);

//B�squeda en Profundidad Limitada
int busquedaProfundidadLimitada(int limite);



//B�squeda Voraz
LISTA InsertarOrdenadoVoraz(LISTA C, tNodo* nuevo);
LISTA	ordenarListaVoraz(LISTA	A, LISTA Suc);
int busquedaVoraz();

//B�squeda A*
LISTA InsertarOrdenadoA(LISTA C, tNodo* nuevo);
LISTA ordenarListaA(LISTA	A, LISTA	Suc);
int busquedaA();


void solucionFin(int res);
