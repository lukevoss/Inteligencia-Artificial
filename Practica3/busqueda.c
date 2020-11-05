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
        printf("\n Desde el inicio\n");
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


/* Crea el nodo ra�z. */
tNodo *nodoInicial(){
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));
   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   inicial->valHeuristica = piezasMalColocadas(inicial->estado);
   return inicial;
}

LISTA expandir(tNodo *nodo){
    unsigned op;
    LISTA sucesores=VACIA;
    tNodo *nuevo=calloc(1,sizeof(tNodo));
    tEstado *s;
    for (op=1; op<=NUM_OPERADORES;op++){
      if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
          s=aplicaOperador(op,nodo->estado);
          nuevo->estado=s;
          nuevo->padre=nodo;
          nuevo->operador=op;
          nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
          nuevo->profundidad=nodo->profundidad+1;
          nuevo->valHeuristica = piezasMalColocadas(nuevo->estado);
          InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));
      }
  }
return sucesores;
}

//encontrar un nodo en una lista
//DONE
LISTA* find_node(LISTA *head, tEstado *estado_actual) {
    LISTA *tmp = head;
    while (tmp != NULL) {
        tNodo* nodo = (*tmp)->nodo;
        if (iguales(nodo->estado, estado_actual)) return tmp;
        tmp = (*tmp)->next;
    }
    return NULL;
}

//void mysort(LISTA* head, LISTA* p1, LISTA* p2)
//{
//    LISTA temp2 = *p2;
//    if (esVacia(temp2))
//    {
//        return;
//    }
//    LISTA temp1 = p1;
//    LISTA* p3 = temp1->next;
//    while (p3 != NULL)
//    {
//        int nodo1 = temp1->nodo;
//        if (temp1->nodo > temp2->data)
//        {
//            swap(p1->data, p3->data);
//        }
//        p3 = p3->next;
//    }
//    mysort(head, p2, p2->next);
//}
//
//void ordenarVoraz(LISTA* c) {
//    LISTA aux = VACIA;
//    aux = *c;
//    LISTA aux2 = aux->next;
//    tNodo* Actual = aux->nodo;
//    tNodo* Siguente = aux2->nodo;
//    if (Siguente->valHeuristica < Actual->valHeuristica) {
//        aux->next = aux2->next;
//        aux2->next = aux;
//    }
//} 


//B�squeda en Anchura
//DONE
int busquedaAnchura(){
    int objetivo=0, visitados=0, expansiones=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

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
            Abiertos=Concatenar(Abiertos,Sucesores);
            expansiones++;
      }
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("Expansiones= %d\n", expansiones);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

//B�squeda en Profundidad
//DONE
int busquedaProfundidad() {
    int objetivo = 0, visitados = 0, expansiones = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();

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
            Abiertos = Concatenar(Abiertos, Sucesores);
            expansiones++;
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    printf("Expansiones= %d\n", expansiones);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

//B�squeda en Anchura con Control de Estados Repetidos
int busquedaAnchurasinRep() {
    int objetivo = 0, visitados = 0, expansiones = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
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
        LISTA nuevoCerrados = VACIA;

        //deep copy of Cerrados to nuevoCerrados
        nuevoCerrados = CopiarLista(Cerrados);

        while(!esVacia(nuevoCerrados)){
            tNodo* cerradoActual = (tNodo*)calloc(1, sizeof(tNodo));
            cerradoActual = (tNodo*)calloc(1, sizeof(tNodo));
            ExtraerPrimero(nuevoCerrados, cerradoActual, sizeof(tNodo));
            EliminarPrimero(&nuevoCerrados);
            yaVisto = iguales(cerradoActual->estado, Actual->estado);
            if (yaVisto == 1) {
                printf("\nseen this MF");
                break;
            }
        }
        
        //TODO: control if costeCamino of cerradoActual is smaller than Actual (not a must)

        if (!objetivo  && !yaVisto) { //prueba si el nodo ya ha sido visitado
            Sucesores = expandir(Actual);
            Abiertos = Concatenar(Abiertos, Sucesores);
            expansiones++;
            Cerrados = expandir(Actual);
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    printf("Expansiones= %d\n", expansiones);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

//B�squeda en Profundidad con Control de Estados Repetidos
//int busquedaProfundidadsinRep() {
//    int objetivo = 0, visitados = 0, expansiones = 0;
//    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
//    tNodo* Inicial = nodoInicial();
//    LISTA Abiertos = VACIA;
//    LISTA Sucesores = VACIA;
//    LISTA Cerrados = VACIA;
//    InsertarPrimero(&Abiertos, (tNodo*)Inicial, sizeof(tNodo));
//    while (!esVacia(Abiertos) && !objetivo) {
//        Actual = (tNodo*)calloc(1, sizeof(tNodo));
//        ExtraerUltimo(Abiertos, Actual, sizeof(tNodo));
//        EliminarUltimo(&Abiertos);
//        visitados++; //aumentar en 1
//        objetivo = testObjetivo(Actual->estado);
//
//        int yaVisto = 0;
//        LISTA nuevoCerrados = VACIA;
//        tNodo* cerradoActual = (tNodo*)calloc(1, sizeof(tNodo));
//        //make deep copy of Cerrados to nuevoCerrados
//        nuevoCerrados = CopiarLista(Cerrados);
//
//        while (!esVacia(nuevoCerrados)) {
//            cerradoActual = (tNodo*)calloc(1, sizeof(tNodo));
//            ExtraerPrimero(nuevoCerrados, cerradoActual, sizeof(tNodo));
//            EliminarPrimero(&nuevoCerrados);
//            yaVisto = iguales(cerradoActual->estado, Actual->estado);
//            if (yaVisto == 1) {
//                printf("\nseen this MF");
//                break;
//            }//if
//        }//while
//        if (!objetivo) { //prueba si el nodo ya ha sido visitado
//            Sucesores = expandir(Actual);
//            Abiertos = Concatenar(Abiertos, Sucesores);
//            expansiones++;
//            Cerrados = expandir(Actual);
//        }
//    }//while
//
//    printf("\nVisitados= %d\n", visitados);
//    printf("Expansiones= %d\n", expansiones);
//    if (objetivo)
//        dispSolucion(Actual);
//    free(Sucesores);
//    free(Inicial);
//    free(Actual);
//    return objetivo;
//}


int busquedaProfundidadsinRep() {
    int objetivo = 0, visitados = 0, expansiones = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();
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
        if (igualnodo != NULL) {
            yaVisto = 1;
            dispEstado(Actual->estado);
            printf("iguales :\n");
            tNodo* nodo = (*igualnodo)->nodo;
            dispEstado(nodo->estado);
        }//if

        if (!objetivo && !yaVisto) { //prueba si el nodo ya ha sido visitado
            Sucesores = expandir(Actual);
            Abiertos = Concatenar(Abiertos, Sucesores);
            expansiones++;
            Cerrados = expandir(Actual);
        }//if
    }//while

    printf("\nVisitados= %d\n", visitados);
    printf("Expansiones= %d\n", expansiones);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}


//B�squeda en Profundidad Limitada
//DONE
int busquedaProfundidadLimitada(int limite) {
    int objetivo = 0, visitados = 0, expansiones = 0;
    tNodo* Actual = (tNodo*)calloc(1, sizeof(tNodo));
    tNodo* Inicial = nodoInicial();

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
            Abiertos = Concatenar(Abiertos, Sucesores);
            expansiones++;
        }
    }//while
    printf("\nVisitados= %d\n", visitados);
    printf("Expansiones= %d\n", expansiones);
    if (objetivo)
        dispSolucion(Actual);
    //free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//                                  Busqueda Informada
//////////////////////////////////////////////////////////////////////////////////////////////

// Entrada:
// LISTA C: C es una lista vac�a u ordenada de nodos
// tNodo *nuevo: es un nodo de b�squeda
// Devuelve una Lista de elementos
LISTA InsertarOrdenado(LISTA C, tNodo* nuevo) {
    //inicializaciones de las variables temporales
    LISTA R = VACIA;
    tNodo* nc = (tNodo*)calloc(1, sizeof(tNodo));

    // nc es un tNodo que ira guardando nodos de la lista C
   // R es una lista vac�a al inicio y ser� la lista resultante del siguiente proceso

    if (esVacia(C)) 
        InsertarUltimo(&R, nuevo, sizeof(tNodo));
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