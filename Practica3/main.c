/*******************************************/
/*             MAIN.C                      */
/*                                         */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "puzle.h"
#include "listaia.h"
#include "busqueda.h"

int main(){
    ////test usar lista como stack
    //LISTA test = NULL;
    //InsertarUltimo()
    solucionFin(busquedaProfundidadLimitada(3));

    return 0;
}
