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



tNodo* minimax(tNodo *t, int jugador) {
     int mejorJugada = -1;
     int max_actual, jugada;
     int max = -10000;
     tNodo *intento=malloc(sizeof(tNodo));
     printf("\n Mi turno: \n");
     for(jugada = 0; jugada < 9; ++jugada){
      if (esValida(t,jugada)) {
            intento=aplicaJugada(t,1,jugada); //Intenta jugada
            max_actual = valorMin(intento); // Calcula el valor minimax
            if(max_actual > max) {
              max = max_actual;
              mejorJugada = jugada;
            }
      }
     }//for
      t=aplicaJugada(t,jugador,mejorJugada);
      return t;
}

tNodo *jugadaAdversario(tNodo *t) {
     int jugada = 0;
     printf("\nJugada ([0..8])?: ");
     scanf_s("%d", &jugada);
     while (!esValida(t,jugada))
     {
        printf("\n Intenta otra posicion del tablero \n");
        printf("\n");
        printf("\nJugada ([0..8])?: ");
        scanf_s("%d", &jugada);
     }
     t=aplicaJugada(t,-1,jugada);
     return t;
}




