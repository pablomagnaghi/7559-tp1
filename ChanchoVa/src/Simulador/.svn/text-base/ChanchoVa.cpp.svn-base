#include <iostream>
#include <string>
#include <stdlib.h>
#include "OptionsParser.h"
#include "Juego.h"

using namespace std;

void imprimirModoDeUso(){
	cout << endl << "MODO DE USO:" << endl << endl;
	cout << "	./ChanchoVa opciones" << endl <<endl;
	cout << "	Opciones:" << endl;
	cout << "			-n --num-jugadores <cant>: cantidad de jugadores (2 a" << NUM_JUGADORES_MAX << ")" << endl;
	cout << "			-d --debug (opcional): ejecutar en modo debug" << endl;
}

int main(int argc, char* argv[] ) {
	OptionsParser opParser(argv, argc);

	int cantidadJugadores = atoi(opParser.getOptionValue("-n", "--num-jugadores").c_str());
	if (cantidadJugadores > NUM_JUGADORES_MAX || cantidadJugadores == 0) {
		cout << endl << "ERROR: Cantidad de jugadores inválida." << endl;
		imprimirModoDeUso();
		return -1;
	}

	bool debug = opParser.optionExists("-d", "--debug");

	system("rm -R ./resources/* ");

	Juego juego(cantidadJugadores);
	juego.setDebugMode(debug);
	juego.simular();

	return 0;
}
