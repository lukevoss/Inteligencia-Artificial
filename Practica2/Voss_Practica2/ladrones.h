#pragma once
#define IZQUIERDA 1
#define DERECHA 2
#define N 8 //^N° de sacos en la cinta
#define NUM_OPERADORES 2

#ifndef _tEstado_
#define _tEstado_
typedef struct {
    int C[N];
    int L, B, izq, der;
} tEstado;
#endif

static int C_inicial[N] = { 4,3,2,5,7,1,8,6 };

/* Genera el estado inicial */
tEstado* estadoInicial();

/* Muestra el contenido de la cinta. */
void dispEstado(tEstado* estado);

/* Muestra el nombre de cada operador: Izquierda, Derecha. */
void dispOperador(unsigned op);

/* Comprueba si es posible aplicar un operador a una configuración determinada para la Cinta.
  Devuelve 1 si el movimiento es válido y 0 en otro caso. */
int esValido(unsigned op, tEstado* estado);

/* Aplica un operador a una configuración concreta de la Cinta.
  Devuelve la nueva configuración de la Cinta tras el movimiento. */
tEstado* aplicaOperador(unsigned op, tEstado* estado);

/* Devuelve 1 si un estado es igual al estado objetivo. */
int testObjetivo(tEstado* estado);
