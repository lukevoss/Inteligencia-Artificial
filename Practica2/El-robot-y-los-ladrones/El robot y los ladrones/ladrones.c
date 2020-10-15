#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ladrones.h"


tEstado* estadoInicial()
{
    tEstado* estado = (tEstado*)malloc(sizeof(tEstado));
    for (int i=0; i < N; i++) { //crear cinta
        estado->C[i] = C_inicial[i];
    }
    estado->L = 0;
    estado->B = 0;
    estado->izq = 0;
    estado->der = N-1;
    return estado;
}

void dispEstado(tEstado *estado)
{
   for (int i=0; i<N; i++)
   {
      printf("| %d |",estado->C[i]);
   }
   printf("\n");
}

void dispOperador(unsigned op)
{
    switch (op)
    {
    case IZQUIERDA: printf("AI coge de la IZQUIERDA:\n"); break;
    case DERECHA:   printf("AI coge de la DERECHA:\n"); break;
    }
}


int testObjetivo(tEstado* estado)
{
    return ((estado->izq == estado->der) && (estado->L > estado->B));
}

int esValido(unsigned op, tEstado* estado)
{
    printf("estado derecha: %d \n", estado->der);//TODO
    printf("estado izguierda: %d \n", estado->izq);//TODO
    return ((estado->der - estado->izq) >= 2);
}

tEstado* aplicaOperador(unsigned op, tEstado* estado)
{
    tEstado* nuevo = (tEstado*)malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));  // Hace una copia del estado
    int pos;
    switch (op)
    {
    case IZQUIERDA:
        pos = nuevo->izq;
        nuevo->izq += 1;
        break;
    case DERECHA:
        pos = nuevo->der;
        nuevo->der -= 1;
        break;
    default:
        printf("ERROR 001: SYSTEM CRASHED");
        break;
    }
    nuevo->L += nuevo->C[pos];
    nuevo->C[pos] = 0; //TODO with List, for testing
    nuevo->B += nuevo->C[nuevo->der]; //Robot picks right 
    nuevo->C[nuevo->der] = 0;//TODO with List, for testing
    nuevo->der -= 1;

    return nuevo;
}
