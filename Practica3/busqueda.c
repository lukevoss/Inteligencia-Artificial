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


/* Crea el nodo raíz. */
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

LISTA* find_node(LISTA* head, tEstado estado_actual) {
    LISTA tmp = head;
    while (tmp != NULL) {
        if (igual(tmp->nodo, estado_actual)) return tmp;
        tmp = tmp->next;
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


//Búsqueda en Anchura
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

//Búsqueda en Profundidad
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

//Búsqueda en Anchura con Control de Estados Repetidos
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

//Búsqueda en Profundidad con Control de Estados Repetidos
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
        LISTA nuevoCerrados = VACIA;
        tNodo* cerradoActual = (tNodo*)calloc(1, sizeof(tNodo));
        //make deep copy of Cerrados to nuevoCerrados
        nuevoCerrados = CopiarLista(Cerrados);

        while (!esVacia(nuevoCerrados)) {
            cerradoActual = (tNodo*)calloc(1, sizeof(tNodo));
            ExtraerPrimero(nuevoCerrados, cerradoActual, sizeof(tNodo));
            EliminarPrimero(&nuevoCerrados);
            yaVisto = iguales(cerradoActual->estado, Actual->estado);
            if (yaVisto == 1) {
                printf("\nseen this MF");
                break;
            }//if
        }//while
        if (!objetivo) { //prueba si el nodo ya ha sido visitado
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

//Búsqueda en Profundidad Limitada
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
