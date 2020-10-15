#include "ladrones.h"

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
	op = 2;
	dispOperador(op);
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

	if (esValido(op, estado)) {
		estado = aplicaOperador(op, estado);
		dispEstado(estado);
	}
	else {
		printf("Not allowed\n");
	}

	// TODO shows Not allowed, last pick
	if (esValido(op, estado)) {
		estado = aplicaOperador(op, estado);
		dispEstado(estado);
	}
	else {
		printf("Not allowed\n");
	}
	

	/*bool = testobjetivo(nuevo);
	if (bool == 0) printf("final formation is not achieved\n");
	else printf("final formation achieved\n");*/

	return 0;
}