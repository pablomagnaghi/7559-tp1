#include "ManoReceptora.h"

ManoReceptora::ManoReceptora(char **argv) {
	this->jugador = argv[1];
	this->jugadorIzquierda = argv[2];
	this->nombre = "Jugador [" + this->jugador + "]";
	this->ronda = argv[3];
	this->modoDebug = atoi(argv[4]);
	this->logManager.setDebugMode(modoDebug);
}

void ManoReceptora::recibir() {
	string nombreArchivo = ARCHIVO_FIFO_MANO;
	nombreArchivo +=  this->jugadorIzquierda + this->jugador;
	Fifo mano(nombreArchivo.c_str());

	char carta [ BUFFSIZE ];
	int bytesLeidos = mano.leer ( carta, BUFFSIZE );
	carta[bytesLeidos] = '\0';

	mano.cerrar ();
	actualizarCartaJugador(carta);
}

void ManoReceptora::actualizarCartaJugador(char *carta) {
	string nombreArchivo = ARCHIVO_FIFO_CARTA_RECIBIDA;
	nombreArchivo += this->jugador;
	Fifo fifoCartaRecibida (nombreArchivo.c_str());

	string sCarta = carta;
	//string mensaje = this->nombre + ": Recibo la carta " + sCarta + " del jugador [" + this->jugadorIzquierda + "]";
	//logManager.logMessage(PROCESO_MANO_RECEPTORA,mensaje);

	fifoCartaRecibida.escribir (carta, sCarta.size());
	fifoCartaRecibida.cerrar ();
	fifoCartaRecibida.eliminar ();
}

ManoReceptora::~ManoReceptora() {
	//string mensaje = "Termine mi participacion en la ronda :" + this->ronda + " como receptora del jugador [" + this->jugador + "]";
	//logManager.logMessage(PROCESO_MANO_RECEPTORA, mensaje);
}

