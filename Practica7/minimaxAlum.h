/*******************************************/
/* 		    minimaxAlum.h                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

tNodo* minimax(tNodo* t, int jugador);
int valorMin(tNodo* t, int profundidad);
int valorMax(tNodo* t, int profundidad);
tNodo* jugadaAdversario(tNodo* t);
int valorMin_ab(tNodo* t, int prof, int alfa, int beta);
int valorMax_ab(tNodo* t, int prof, int alfa, int beta);
tNodo* poda_ab(tNodo* t, int jugador);