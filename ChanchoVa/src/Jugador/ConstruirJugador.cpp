#include "Jugador.h"

// Primer argumento: su numero de jugador
// Segundo argumento: la cantidad maxima de jugadores
// Tercer argumento: semIdInicio
// Cuarto argumento: semIdChancho
// Quinto argumento: modoDebug
int main(int argc, char* argv[]) {
	Jugador unJugador = Jugador(argv);

	unJugador.jugar();

	return 0;
}
