/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "puzle.h"
#include "listaia.h"
#include "busqueda.h"


void solucionFin(int res){
   printf("\nFin de la busqueda\n");
    if (res)
      printf("Se ha llegado al objetivo\n");
   else
      printf("No se ha llegado al objetivo\n");
}
void dispNodo(tNodo *nodo){
    dispEstado(nodo->estado);
    printf("\n");
}
void dispCamino(tNodo *nodo){
    if (nodo->padre==NULL){
        printf("\nDesde el inicio\n");
        dispEstado(nodo->estado);
    }
    else {
        dispCamino(nodo->padre);
         dispOperador(nodo->operador);
        dispEstado(nodo->estado);
    }
}

void dispSolucion(tNodo *nodo){
   printf("Profundidad=%d\n",nodo->profundidad);
   printf("Coste=%d\n",nodo->costeCamino);
   dispCamino(nodo);
}


/* Crea el nodo raíz. */
tNodo *nodoInicial(){
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));
   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   inicial->valHeuristica = 0; // CHANGE: piezasMalColocadas(inicial->estado);
   return inicial;
}

LISTA expandir(tNodo *nodo){
    unsigned op;
    LISTA sucesores=VACIA;
    tNodo *nuevo=calloc(1,sizeof(tNodo));
    tEstado *s;
    tEstado *o = estadoObjetivo(); //para Manhatten
    for (op=1; op<=NUM_OPERADORES;op++){
      if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
          s=aplicaOperador(op,nodo->estado);
          nuevo->estado=s;
          nuevo->padre=nodo;
          nuevo->operador=op;
          nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
          nuevo->profundidad=nodo->profundidad+1;
          nuevo->valHeuristica = manhatten(nuevo->estado, o);//CHANGE: piezasMalColocadas(nuevo->estado);
          InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));
      }
  }
return sucesores;
}

//encontrar un nodo en una lista
//DONE
LISTA* find_node(LISTA *head, tEstado *estado_actual) {
    LISTA *tmp = head;
    while (tmp != NULL && *tmp != NULL) {
        tNodo* nodo = (*tmp)->nodo;
        if (iguales(nodo->estado, estado_actual)) return tmp;
        tmp = (*tmp)->next;
    }
    return NULL;
}



//Búsqueda en Anchura
//DONE
int busquedaAnchura(){
    int objetivo=0, visitados=0, generados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();
    generados++;
    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        visitados++; //aumentar en 1
        objetivo=testObjetivo(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            generados += LongitudLista(Sucesores);
            Abiertos=Concatenar(Abiertos,Sucesores);
      }
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("Generados= %d\n", generados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

//Búsqueda en Profundidad
//DONE
int busquedaProfundidad() {
    int objetivo = 0, visitados = 0, generados = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
    generados++;
    LISTA Abiertos = VACIA;
    LISTA Sucesores = VACIA;
    InsertarPrimero(&Abiertos, (tNodo*)Inicial, sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo) {
        Actual = (tNodo*)calloc(1, sizeof(tNodo));
        ExtraerUltimo(Abiertos, Actual, sizeof(tNodo));
        EliminarUltimo(&Abiertos);
        visitados++;
        objetivo = testObjetivo(Actual->estado);
        if (!objetivo) {
            Sucesores = expandir(Actual);
            generados += LongitudLista(Sucesores);
            Abiertos = Concatenar(Abiertos, Sucesores);
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    printf("Generados= %d\n", generados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

//Búsqueda en Anchura con Control de Estados Repetidos
//DONE
int busquedaAnchurasinRep() {
    int objetivo = 0, visitados = 0, generados = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
    generados++;
    LISTA Abiertos = VACIA;
    LISTA Sucesores = VACIA;
    LISTA Cerrados = VACIA;
    InsertarPrimero(&Abiertos, (tNodo*)Inicial, sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo) {
        Actual = (tNodo*)calloc(1, sizeof(tNodo));
        ExtraerPrimero(Abiertos, Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        visitados++; //aumentar en 1
        objetivo = testObjetivo(Actual->estado);

        int yaVisto = 0;
        LISTA* igualnodo = find_node(Cerrados, Actual->estado);
        if (igualnodo != NULL) yaVisto = 1;
        else InsertarPrimero(&Cerrados, (tNodo*)Actual, sizeof(tNodo));

        if (!objetivo && !yaVisto) { //prueba si el nodo ya ha sido visitado
            Sucesores = expandir(Actual);
            generados += LongitudLista(Sucesores);
            Abiertos = Concatenar(Abiertos, Sucesores);
        }//if
    }//while

    printf("\nVisitados= %d\n", visitados);
    printf("Generados= %d\n", generados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

//Búsqueda en Profundidad con Control de Estados Repetidos
//DONE
int busquedaProfundidadsinRep() {
    int objetivo = 0, visitados = 0, generados = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
    generados++;
    LISTA Abiertos = VACIA;
    LISTA Sucesores = VACIA;
    LISTA Cerrados = VACIA;
    InsertarPrimero(&Abiertos, (tNodo*)Inicial, sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo) {
        Actual = (tNodo*)calloc(1, sizeof(tNodo));
        ExtraerUltimo(Abiertos, Actual, sizeof(tNodo));
        EliminarUltimo(&Abiertos);
        visitados++; //aumentar en 1
        objetivo = testObjetivo(Actual->estado);

        int yaVisto = 0;
        LISTA* igualnodo = find_node(Cerrados, Actual->estado);
        if (igualnodo != NULL) yaVisto = 1;
        else InsertarPrimero(&Cerrados, (tNodo*)Actual, sizeof(tNodo));

        if (!objetivo && !yaVisto) { //prueba si el nodo ya ha sido visitado
            Sucesores = expandir(Actual);
            generados += LongitudLista(Sucesores);
            Abiertos = Concatenar(Abiertos, Sucesores);
        }//if
    }//while

    printf("\nVisitados= %d\n", visitados);
    printf("Generados= %d\n", generados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}


//Búsqueda en Profundidad Limitada
//DONE
int busquedaProfundidadLimitada(int limite) {
    int objetivo = 0, visitados = 0, generados = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
    generados++;
    LISTA Abiertos = VACIA;
    LISTA Sucesores = VACIA;
    InsertarPrimero(&Abiertos, (tNodo*)Inicial, sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo) {
        Actual = (tNodo*)calloc(1, sizeof(tNodo));
        ExtraerUltimo(Abiertos, Actual, sizeof(tNodo));
        EliminarUltimo(&Abiertos);
        visitados++;
        objetivo = testObjetivo(Actual->estado);
        if (!objetivo && Actual->profundidad <= (limite-1))
        {
            Sucesores = expandir(Actual);
            generados += LongitudLista(Sucesores);
            Abiertos = Concatenar(Abiertos, Sucesores);
        }
    }//while
    printf("\nVisitados= %d\n", visitados);
    printf("Generados= %d\n", generados);
    if (objetivo)
        dispSolucion(Actual);
    //free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//                                  Busqueda Informada Voraz
//////////////////////////////////////////////////////////////////////////////////////////////

// Entrada:
// LISTA C: C es una lista vacía u ordenada de nodos
// tNodo *nuevo: es un nodo de búsqueda
// Devuelve una Lista de elementos
LISTA InsertarOrdenadoVoraz(LISTA C, tNodo* nuevo) {
    //inicializaciones de las variables temporales
    LISTA R = VACIA; // R es una lista vacía al inicio y será la lista resultante del siguiente proceso
    tNodo* nc = (tNodo*)calloc(1, sizeof(tNodo)); // nc es un tNodo que ira guardando nodos de la lista C

    if (esVacia(C)) 
        InsertarPrimero(&R, nuevo, sizeof(tNodo));
    else {
        ExtraerPrimero(C, nc, sizeof(tNodo));
        while (!esVacia(C) && nc->valHeuristica < nuevo->valHeuristica)
        {
            InsertarUltimo(&R, nc, sizeof(tNodo));
            C = C->next;
            if (!(esVacia(C)))
                ExtraerPrimero(C, nc, sizeof(tNodo));
        }//while
        InsertarUltimo(&R, nuevo, sizeof(tNodo));
        R = Concatenar(R, C);
     }//else

    return R;
}

//LISTA	ordenarLista(LISTA	A,	LISTA	Suc)
//A	es una lista ordenada o	vacía
//Suc es una lista de	nodos en	cualquier orden
//Devuelve una lista ordenada conteniendo todoslos	elementosde	A	y	Suc
LISTA	ordenarListaVoraz(LISTA	A, LISTA Suc) {
    /*Insercion ordenada de	nodos sucesores en	la	lista ordenada A	*/
    tNodo* aux = (tNodo*)calloc(1, sizeof(tNodo));
    while (!esVacia(Suc)) {
        ExtraerPrimero(Suc, aux, sizeof(tNodo));
        EliminarPrimero(&Suc);
        A = InsertarOrdenadoVoraz(A, aux);
    }
    return(A);//Devuelve	la	lista	ordenada
}//ordenarLista

//Búsqueda Voraz
//DONE
int busquedaVoraz() {
    int objetivo = 0, visitados = 0, generados = 0;;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
    generados++;
    LISTA Cerrados = VACIA;
    LISTA Abiertos = VACIA;
    LISTA Sucesores = VACIA;
    InsertarPrimero(&Abiertos, (tNodo*)Inicial, sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo) {
        Actual = (tNodo*)calloc(1, sizeof(tNodo));
        ExtraerPrimero(Abiertos, Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        visitados++;
        objetivo = testObjetivo(Actual->estado);
        if (!objetivo) {
            //repe = buscaRepeHeu(Actual, Cerrados, tipo);
            LISTA* igualnodo = find_node(Cerrados, Actual->estado);
            if (esVacia(igualnodo)) {
                Sucesores = expandir(Actual);
                generados += LongitudLista(Sucesores);
                Abiertos = ordenarListaVoraz(Abiertos, Sucesores);
                InsertarPrimero(&Cerrados, (tNodo*)Actual, sizeof(tNodo));
            }
        }//objetivo
    }//while
    printf("Visitados= %d\n", visitados);
    printf("Generados= %d\n", generados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                  Busqueda Informada A*
//////////////////////////////////////////////////////////////////////////////////////////////

// Entrada:
// LISTA C: C es una lista vacía u ordenada de nodos
// tNodo *nuevo: es un nodo de búsqueda
// Devuelve una Lista de elementos
LISTA InsertarOrdenadoA(LISTA C, tNodo* nuevo) {
    //inicializaciones de las variables temporales
    LISTA R = VACIA; // R es una lista vacía al inicio y será la lista resultante del siguiente proceso
    tNodo* nc = (tNodo*)calloc(1, sizeof(tNodo)); // nc es un tNodo que ira guardando nodos de la lista C

    if (esVacia(C))
        InsertarPrimero(&R, nuevo, sizeof(tNodo));
    else {
        ExtraerPrimero(C, nc, sizeof(tNodo));
        while (!esVacia(C) &&  (nc->valHeuristica + nc->costeCamino) < (nuevo->valHeuristica + nuevo->costeCamino))
        {
            InsertarUltimo(&R, nc, sizeof(tNodo));
            C = C->next;
            if (!(esVacia(C)))
                ExtraerPrimero(C, nc, sizeof(tNodo));
        }//while
        InsertarUltimo(&R, nuevo, sizeof(tNodo));
        R = Concatenar(R, C);
    }//else

    return R;
}

//LISTA	ordenarLista(LISTA	A,	LISTA	Suc)
//A	es una lista ordenada o	vacía
//Suc es una lista de	nodos en	cualquier orden
//Devuelve una lista ordenada conteniendo todoslos	elementosde	A	y	Suc
LISTA ordenarListaA(LISTA A, LISTA Suc) {
    /*Insercion ordenada de	nodos sucesores en	la	lista ordenada A	*/
    tNodo* aux = (tNodo*)calloc(1, sizeof(tNodo));
    while (!esVacia(Suc)) {
        ExtraerPrimero(Suc, aux, sizeof(tNodo));
        EliminarPrimero(&Suc);
        A = InsertarOrdenadoA(A, aux);
    }
    return(A);//Devuelve	la	lista	ordenada
}//ordenarLista

//Búsqueda Voraz
//DONE
int busquedaA() {
    int objetivo = 0, visitados = 0, generados = 0;;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
    generados++; //primer nodo es generado
    LISTA Cerrados = VACIA;
    LISTA Abiertos = VACIA;
    LISTA Sucesores = VACIA;
    InsertarPrimero(&Abiertos, (tNodo*)Inicial, sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo) {
        Actual = (tNodo*)calloc(1, sizeof(tNodo));
        ExtraerPrimero(Abiertos, Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        visitados++;
        objetivo = testObjetivo(Actual->estado);
        if (!objetivo) {
            //repe = buscaRepeHeu(Actual, Cerrados, tipo);
            LISTA* igualnodo = find_node(Cerrados, Actual->estado);
            if (esVacia(igualnodo)) {
                Sucesores = expandir(Actual);
                generados += LongitudLista(Sucesores);
                Abiertos = ordenarListaA(Abiertos, Sucesores);
                InsertarPrimero(&Cerrados, (tNodo*)Actual, sizeof(tNodo));
            }
        }//objetivo
    }//while
    printf("Visitados= %d\n", visitados);
    printf("Generados= %d\n", generados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}