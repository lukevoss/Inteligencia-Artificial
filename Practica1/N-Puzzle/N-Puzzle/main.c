#include "puzle.h"

int main() {

	//////////////////////////Test estadoInicial, dispEstado, dispOperador, crearEstado //////////////////////////////////////
	int op = 1;
	tEstado* estado = estadoInicial();
	dispEstado(estado);
	dispOperador(op);

	//////////////////////////////////test esValido y aplicaOperador//////////////////////////////////////////////
	if (esValido(op, estado)) {
		estado = aplicaOperador(op, estado);
		dispEstado(estado);
	}
	else {
		printf("Not allowed\n");
	}	
	op = 4;
	if (esValido(op, estado)) {
		estado = aplicaOperador(op, estado);
		dispEstado(estado);
	}
	else {
		printf("Not allowed\n");
	}

	////////////////////////////////////Test testObjetivo y estadoObjetivo//////////////////////////////////////////
	int bool = testObjetivo(estado);
	if (bool == 0) printf("Final Formation is not achieved\n");
	else printf("Final Formation achieved\n");
	tEstado* nuevo = estadoObjetivo();
	bool = testObjetivo(nuevo);
	if (bool == 0) printf("Final Formation is not achieved\n");
	else printf("Final Formation achieved\n");

	//////////////////////////////////////Test iguales/////////////////////////////////////////////////////////////
	op = 2;
	dispOperador(op);
	if (esValido(op, estado)) {
		estado = aplicaOperador(op, estado);
		dispEstado(estado);
	}
	tEstado* nuevo_inicial = estadoInicial();
	bool = iguales(estado, nuevo_inicial);
	if (bool == 0) printf("The Two Tables are different\n");
	else printf("The Two Tables are the same!\n");
	return 0;
}