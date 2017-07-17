#include "ManoEnviadora.h"

// Primer argumento: numero de jugador a izquierda
// Segundo argumento: numero de jugador a derecha
// Tercer argumeto: carta a enviar
// Cuarto argumento: modoDebug
int main(int argc, char* argv[]) {

	ManoEnviadora mano = ManoEnviadora(argv);

	mano.enviar(argv[3]);

	return 0;
}



