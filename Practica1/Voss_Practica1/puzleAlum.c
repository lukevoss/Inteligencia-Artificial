/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzle.h"



tEstado *crearEstado(int puzle[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=puzle[i][j];
         estado->celdas[i][j]=ficha;
         estado->fila[ficha]=i;
         estado->col[ficha]=j;
      }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACIÓN DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Función auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)  //
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (s->celdas[i][j] != t->celdas[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}


int testObjetivo(tEstado *estado)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (estado->celdas[i][j] != puzle_final[i][j])
                return 0;//break if two values are not the same
        }
    }
    return 1;
}


int esValido(unsigned op, tEstado *estado)
{
    int valido = 0;
    switch (op)
    {
    case ARRIBA:
        valido = s->fila[0] != 0; //prueba si la fila es valido para ir arriba
        break;
    case ABAJO:
        valido = s->fila[0] != 2; //prueba si la fila es valido para ir abajo
        break;
    case IZQUIERDA:
        valido = s->col[0] != 0; //prueba si la columna es valido para ir a la izquierda
        break;
    case DERECHA:
        valido = s->col[0] != 2; //prueba si la columna es valido para ir a la derecha
        break;
    default:
        valido = 0;
        break;
    }
    return valido;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
     tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado
    int temp = 0;
    switch (op) //cambiar matriz
    {
    case ARRIBA:
        temp = nuevo->celdas[nuevo->fila[0] - 1][nuevo->col[0]];
        nuevo->celdas[nuevo->fila[0] - 1][nuevo->col[0]] = 0;
        nuevo->celdas[nuevo->fila[0]][nuevo->col[0]] = temp;
        *nuevo = crearEstado(nuevo->celdas);
        break;
    case ABAJO:
        temp = nuevo->celdas[nuevo->fila[0] + 1][nuevo->col[0]];
        nuevo->celdas[nuevo->fila[0] + 1][nuevo->col[0]] = 0;
        nuevo->celdas[nuevo->fila[0]][nuevo->col[0]] = temp;
        *nuevo = crearEstado(nuevo->celdas);
        break;
    case IZQUIERDA:
        temp = nuevo->celdas[nuevo->fila[0]][nuevo->col[0] - 1];
        nuevo->celdas[nuevo->fila[0]][nuevo->col[0] - 1] = 0;
        nuevo->celdas[nuevo->fila[0]][nuevo->col[0]] = temp;
        *nuevo = crearEstado(nuevo->celdas);
        break;
    case DERECHA:
        temp = nuevo->celdas[nuevo->fila[0]][nuevo->col[0] + 1];
        nuevo->celdas[nuevo->fila[0]][nuevo->col[0] + 1] = 0;
        nuevo->celdas[nuevo->fila[0]][nuevo->col[0]] = temp;
        *nuevo = crearEstado(nuevo->celdas);
        break;
    default:
        break;
    }
    return nuevo;
}




