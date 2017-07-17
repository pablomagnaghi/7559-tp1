#ifndef MANOENVIADORA_H_
#define MANOENVIADORA_H_

#include <string>
#include "../Concurrencia/Fifo/Fifo.h"
#include "../Common/LogFileManager.h"
#include "../Common/Constants.h"
#include "../Common/Util.h"
#include <stdlib.h>

using namespace std;

class ManoEnviadora {
private:
	LogFileManager logManager;
	string jugador;
	string jugadorDerecha;
	string nombre;
	bool modoDebug;

public:
	ManoEnviadora(char**);
	virtual ~ManoEnviadora();

	void enviar(char*);
};

#endif /* MANOENVIADORA_H_ */
