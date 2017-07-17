#ifndef Jugador_H_
#define Jugador_H_

#include "../Common/Constants.h"
#include "../Common/Util.h"
#include "../Common/LogFileManager.h"
#include "../Concurrencia/Semaforos/Semaforo.h"
#include "../Concurrencia/Semaforos/MemoriaCompartida.h"
#include "../Concurrencia/Fifo/Fifo.h"
#include "../Concurrencia/Seniales/SIGINT_Handler.h"
#include "../Concurrencia/Seniales/SignalHandler.h"

#include <sys/wait.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <iostream>

using namespace std;


class Jugador {
private:
	LogFileManager logManager;

	string pidString;
	int numJugador;
	int cantJugadores;
	int *cartas;
	int numJugadorIzquierda;
	int numJugadorDerecha;
	string nombre;
	bool tengoChancho;
	int posicionCartaEnviada;
	int semIdInicio;
	int semIdChanchoVa;
	vector<int> pidHijos;
	bool modoDebug;

	void inicializarCartas();
	int obtenerJugadorIzquierda(int);
	int obtenerJugadorDerecha(int);

	void esperarInicio(int);
	void leerCartasIniciales();
	void obtenerCartasIniciales(string);
	bool checkChancho();

	void apoyarMano();
	void avisarLaMano();
	void conocerLaMano();

	void mostrarMensajeDeCartas(string);

	int obtenerCartaParaenviar();

public:
	Jugador(char**);
	virtual ~Jugador();

	void jugar();
};

#endif /* Jugador_H_ */
