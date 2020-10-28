/*******************************************/
/*             LISTAIA .C                  */
/*                                         */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaia.h"

int esVacia( LISTA c){
    return (c == VACIA);
}//esVacia

void InsertarPrimero(LISTA *c, void *n, int size){
    LISTA p=(LISTA ) malloc(sizeof(LISTA)+size);
    memcpy((void *)p->nodo,(void*)n, size);
    p->next=(*c);
    *c=p;
}//InsertarPrimero


void ExtraerPrimero(LISTA c, void *n, int size){
    memcpy((void *) n, (void *) c->nodo,size);
};//Extraer primer elemento

void ExtraerUltimo(LISTA c, void* n, int size) {
    LISTA aux;
    aux=c;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    memcpy((void*)n, (void*)aux->nodo, size);
};

void EliminarUltimo(LISTA* c) {
    LISTA aux = VACIA;
    LISTA aux2 = VACIA;
    if (esVacia(c)) {
        printf("es Vacia");
        return 0;
    }
    aux = *c;
    if(esVacia(aux->next))
    {
        printf("aux es Vacia");
        *c = VACIA;
        free(aux);
    }
    else {
        aux2 = aux->next;
        while (aux2->next != NULL) {
            aux = aux->next;
            aux2 = aux2->next;
        }
        aux->next = NULL;
        free(aux2);
        printf("deleted last element");
    }
}//EliminarUltimo



void EliminarPrimero(LISTA *c){
    LISTA p;
    p=*c;
    *c=p->next;
    free(p);
}//Eliminar primer elemento de la lista

void InsertarUltimo(LISTA *c, void *n, int size){
    LISTA p=malloc(sizeof(LISTA)+size);
    LISTA aux=VACIA;
    //creando el nodo
    memcpy((void*)(p->nodo),(void *) n, size);
    p->next=NULL;
    if (esVacia(*c)){
        *c=p;
    }
    else{
        aux=*c;
        while (aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=p;
    }
}//InsertarUltimo

LISTA Concatenar(LISTA c, LISTA p) {
    LISTA aux;
    if (esVacia(c))
        c = p;
    else {
        aux = c;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = p;
    }
    return c;
}//Concatenar

// Function that takes a linked list & returns its complete copy
LISTA CopiarLista(LISTA original)
{
    LISTA current = original;	// used to iterate over original list
    LISTA newList = NULL; // head of the new list
    LISTA tail = NULL;	// point to last node in new list

    while (current != NULL)
    {
        // special case for the first new Node
        if (newList == NULL)
        {
            newList = (LISTA*)malloc(sizeof(LISTA));
            *newList->nodo = current->nodo;
            newList->next = NULL;
            tail = newList;
        }
        else
        {
            tail->next = (LISTA*)malloc(sizeof(LISTA));
            tail = tail->next;
            *tail->nodo = current->nodo;
            tail->next = NULL;
        }
        current = current->next;
    }

    return newList;
}
