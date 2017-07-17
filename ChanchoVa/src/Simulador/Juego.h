#ifndef JUEGO_H_
#define JUEGO_H_

#include "../Common/LogFileManager.h"
#include "../Common/Constants.h"
#include "../Common/Util.h"
#include "../Concurrencia/Seniales/SignalHandler.h"
#include "../Concurrencia/Semaforos/Semaforo.h"
#include "../Concurrencia/Seniales/SIGINT_Handler.h"
#include "../Concurrencia/Fifo/Fifo.h"
#include "../ConsultaTablero/TableroPuntaje.h"

#include <iostream>
#include <sys/wait.h>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include <list>
#include <fstream>
#include <vector>

using namespace std;

class Juego {
public:
	Juego(int cantJug);
	virtual ~Juego();
	void simular();
	void setDebugMode(bool);
private:
	LogFileManager logManager;
	TableroPuntaje* tablero;

	int cantJugadores;
	int cantCartas;
	bool terminado;
	bool modoDebug;

	vector<int> pidJugadores;

	vector<string> cartas;

	void empezarRonda();
	int obtenerNumeroDeCarta(int);
	void mezclarCartas();
	void repartirCartas();
	void avisarChancho(vector <string>);
};

#endif /* JUEGO_H_ */
