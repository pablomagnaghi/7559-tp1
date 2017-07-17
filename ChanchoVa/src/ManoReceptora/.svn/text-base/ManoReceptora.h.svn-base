#ifndef MANORECEPTORA_H_
#define MANORECEPTORA_H_

#include <string>
#include <stdlib.h>
#include <iostream>
#include "../Concurrencia/Fifo/Fifo.h"
#include "../Common/LogFileManager.h"
#include "../Common/Constants.h"
#include "../Common/Util.h"

using namespace std;

class ManoReceptora {
	LogFileManager logManager;
	string jugador;
	string jugadorIzquierda;
	string nombre;
	string ronda;
	bool modoDebug;

	void actualizarCartaJugador(char*);
public:
	ManoReceptora(char **);
	virtual ~ManoReceptora();

	void recibir();
};

#endif /* MANORECEPTORA_H_ */
