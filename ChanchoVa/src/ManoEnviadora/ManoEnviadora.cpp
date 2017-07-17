#include "ManoEnviadora.h"

ManoEnviadora::ManoEnviadora(char **argv) {
	this->jugador = argv[1];
	this->jugadorDerecha = argv[2];
	this->nombre = "Jugador [" + this->jugador + "]";
	this->modoDebug = atoi(argv[4]);
	this->logManager.setDebugMode(modoDebug);
}

void ManoEnviadora::enviar(char *carta) {
	string nombreArchivo = ARCHIVO_FIFO_MANO;
	nombreArchivo += this->jugador + this->jugadorDerecha;

	Fifo mano(nombreArchivo.c_str());

	mano.escribir (carta, strlen(carta) );

	//string sCarta = carta;
	//string mensaje = this->nombre + ": Envio la carta " + sCarta + " al jugador [" + this->jugadorDerecha + "]";
	//logManager.logMessage(PROCESO_MANO_ENVIADORA,mensaje);

	mano.cerrar ();
	mano.eliminar ();
}

ManoEnviadora::~ManoEnviadora() {
	//string mensaje = "Termine mi participacion en esta ronda como enviadora del jugador [" + this->jugador + "]";
	//logManager.logMessage(PROCESO_MANO_ENVIADORA, mensaje);
}
