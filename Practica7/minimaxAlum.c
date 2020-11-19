/*******************************************/
/* 		    minimaxAlum.c                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tictactoe.h"



tNodo *PSEUDOminimax(tNodo *t) {
     int mejorJugada = -1;
     int puntos = -2;
     int i, temp;
     tNodo *intento=malloc(sizeof(tNodo));
     printf("\n Mi turno: \n");
     for(i = 0; i < 9; ++i){
      if (esValida(t,i)) {
            intento=aplicaJugada(t,1,i); //Intenta jugada
            temp =terminal(intento); // Calcula el valor minimax
            if(temp > puntos) {
              puntos = temp;
              mejorJugada = i;
            }
      }}//for
      t=aplicaJugada(t,1,mejorJugada);
      return t;
}

tNodo *jugadaAdversario(tNodo *t) {
     int jugada = 0;
     printf("\nJugada ([0..8])?: ");
     scanf("%d", &jugada);
     while (!esValida(t,jugada))
     {
        printf("\n Intenta otra posicion del tablero \n");
        printf("\n");
        printf("\nJugada ([0..8])?: ");
        scanf("%d", &jugada);
     }
     t=aplicaJugada(t,-1,jugada);
     return t;
}

int valorMax(tNodo* t) {
    int jugada = -1;
    int valor_max = -10000;
    int jugador = 1;
        if (terminal(t))
            valor_max = utilidad(t);
        else {
            for (int i = 0; i < 9; i++) {
                if (esValida(t, i)) {
                    tNodo* intento = malloc(sizeof(tNodo));
                    intento = aplicaJugada(t, 1, i);
                    valor_max = max(valor_max,valorMin(intento));
                }
            }
        }
    return valor_max;
}

int valorMin(tNodo* t) {
    int jugada = -1;
    int valor_min = 10000;
    int jugador = -1;
    if (terminal(t))
        valor_min = utilidad(t);
    else {
        for (int i = 0; i < 9; i++) {
            if (esValida(t, i)) {
                tNodo* intento = malloc(sizeof(tNodo));
                intento = aplicaJugada(t, 1, i);
                valor_min = min(valor_min, valorMin(intento));
            }
        }
    }
    return valor_min;
}