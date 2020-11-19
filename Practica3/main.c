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
    printf("\n---------------------------------------------------------------------------------\n");
    printf("Busqueda A:\n");
    printf("---------------------------------------------------------------------------------\n");
    solucionFin(busquedaA());
    printf("\n---------------------------------------------------------------------------------\n");
    printf("Busqueda Voraz:\n");
    printf("---------------------------------------------------------------------------------\n");
    solucionFin(busquedaVoraz());

    return 0;
}
