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

int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if (winner != 0) return winner * player;

    move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for (i = 0; i < 9; ++i) {//For all moves,
        if (board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player * -1);
            if (thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if (move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; ++i) {
        if (board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if (tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
}

void playerMove(int board[9]) {
    int move = 0;
    do {
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = -1;
}


