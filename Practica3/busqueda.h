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

//B�squeda en Anchura:
int busquedaAnchura(void);

//B�squeda en Profundidad
int busquedaProfundidad(void);

//B�squeda en Anchura:
int busquedaAnchurasinRep(void);

//B�squeda en Profundidad
int busquedaProfundidadsinRep(void);

void solucionFin(int res);