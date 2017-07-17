#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>
#include <stdlib.h>
#include "../../Common/Constants.h"
#include "../../Common/Constants.h"
#include "../../Common/Util.h"
#include "../Fifo/Fifo.h"

#include <sys/wait.h>
#include <string>
#include <iostream>
using namespace std;

#include "EventHandler.h"

class SIGINT_Handler : public EventHandler {

	private:
		sig_atomic_t gracefulQuit;
		string nombre;
		int numJugador;
		int pidHijoIzquierda;
		int pidHijoDerecha;

	public:

		SIGINT_Handler () {
			this->gracefulQuit = 0;
		}

		~SIGINT_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			this->gracefulQuit = 1;

			kill(this->pidHijoDerecha, SIGTERM );
			kill(this->pidHijoIzquierda, SIGTERM );

			string nombreArchivoChancho = ARCHIVO_FIFO_CHANCHO_PERDEDOR;
			Fifo fifoChancho(nombreArchivoChancho.c_str());
			string sNumJugador;
			sNumJugador =+ SEPARADOR;
			sNumJugador += Util::itoa(this->numJugador);

			fifoChancho.escribir((char*)sNumJugador.c_str(), sNumJugador.size());
			fifoChancho.cerrar();

			exit(0);
			return 0;
		}

		void setNumJugador(int num){
			this->numJugador = num;
			this->nombre = "Jugador [" + Util::itoa(num) + "]";
		}

		void setPidsHijos(int pidHijoDerecha, int pidHijoIzquierda) {
			this->pidHijoIzquierda = pidHijoIzquierda;
			this->pidHijoDerecha = pidHijoDerecha;
		}

		sig_atomic_t getGracefulQuit () {
			return this->gracefulQuit;
		}
};

#endif /* SIGINT_HANDLER_H_ */
