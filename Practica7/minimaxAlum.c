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



tNodo* minimax(tNodo* t, int jugador) {
    int mejorJugada = -1;
    int max_actual, jugada;
    int max = -10000;
    tNodo* intento = malloc(sizeof(tNodo));
    printf("\n Mi turno: \n");
    for (jugada = 0; jugada < 9; ++jugada) {
        if (esValida(t, jugada)) {
            intento = aplicaJugada(t, 1, jugada); //Intenta jugada
            max_actual = valorMin(intento); // Calcula el valor minimax
            if (max_actual > max) {
                max = max_actual;
                mejorJugada = jugada;
            }
        }
    }//for
    t = aplicaJugada(t, jugador, mejorJugada);
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

int valorMax(tNodo* t) {
    int jugada = -1;
    int valor_max = -10000;
    int jugador = 1;
        if (t->vacias == 0)
            valor_max = terminal(t);
        else {
            for (int i = 0; i < 9; i++) {
                if (esValida(t, i)) {
                    tNodo* intento = malloc(sizeof(tNodo));
                    intento = aplicaJugada(t, jugador, i);
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
    if (t->vacias == 0)
        valor_min = terminal(t);
    else {
        for (int i = 0; i < 9; i++) {
            if (esValida(t, i)) {
                tNodo* intento = malloc(sizeof(tNodo));
                intento = aplicaJugada(t, jugador, i);
                valor_min = min(valor_min, valorMax(intento));
            }
        }
    }
    return valor_min;
}

tNodo* poda_ab(tNodo* t, int jugador) {
    int mejorJugada = -1;
    int max_actual, jugada, v;
    int max = -10000;
    int alfa = -10000;
    int beta = 10000;
    int prof = 0;
    tNodo* intento = malloc(sizeof(tNodo));
    printf("\n Mi turno: \n");
    for (jugada = 0; jugada < 9; ++jugada) {
        if (esValida(t, jugada)) {
            intento = aplicaJugada(t, 1, jugada); //Intenta jugada
            v = valorMin_ab(intento, prof+1, alfa, beta); // Calcula el valor minimax
            if (v > alfa) {
                alfa = v;
                mejorJugada = jugada;
            }
        }
    }//for
    t = aplicaJugada(t, jugador, mejorJugada);
    return t;
}

#define LIMITE 30

int valorMax_ab(tNodo* t, int prof, int alfa, int beta) {
    int jugada = -1;
    int valor_max = -10000;
    int jugador = 1;
    if (t->vacias == 0)
        valor_max = terminal(t);
    else if (prof == LIMITE)
        valor_max = nodosNoTerminales(t);
    else {
        int i = 0;
        while (i < 9 && alfa < beta) {
            if (esValida(t, i)) {
                tNodo* intento = malloc(sizeof(tNodo));
                intento = aplicaJugada(t, jugador, i);
                alfa = max(alfa, valorMin_ab(intento,prof+1,alfa,beta));
            }
            i++;
        }
        valor_max = alfa;
    }
    return valor_max;
}

int valorMin_ab(tNodo* t, int prof, int alfa, int beta) {
    int jugada = -1;
    int valor_min = 10000;
    int jugador = -1;
    if (t->vacias == 0)
        valor_min = terminal(t);
    else if (prof == LIMITE)
        valor_min = nodosNoTerminales(t);
    else {
        int i = 0;
        while (i < 9 && alfa < beta) {
            if (esValida(t, i)) {
                tNodo* intento = malloc(sizeof(tNodo));
                intento = aplicaJugada(t, jugador, i);
                beta = min(beta, valorMax_ab(intento, prof + 1, alfa, beta));
            }
            i++;
        }
        valor_min = beta;
    }
    return valor_min;
}