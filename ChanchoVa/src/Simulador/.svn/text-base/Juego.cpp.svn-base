#include "Juego.h"

Juego::Juego(int cantJug) {
	this->cantJugadores = cantJug;
	this->cantCartas = cantJug * CARTAS_PARTIDA;
	this->terminado = false;
	this->modoDebug = false;
	string tableroFilePath = TABLERO_FILE_PATH;
	this->tablero = new TableroPuntaje(this->cantJugadores, tableroFilePath);
	logManager.vaciarLog();
	logManager.logMessage(PROCESO_PRINCIPAL,"Bienvenidos al Chancho Va");

	string mensaje = "Cantidad de jugadores: " + Util().itoa(this->cantJugadores);
	logManager.logMessage(PROCESO_PRINCIPAL,mensaje);

	mensaje = "Cantidad de cartas a repartir: " + Util().itoa(this->cantCartas);
	logManager.logMessage(PROCESO_PRINCIPAL,mensaje);
}

void Juego::setDebugMode(bool mode){
	this->logManager.setDebugMode(mode);
	this->modoDebug = mode;
}


void Juego::simular() {
	logManager.logMessage(PROCESO_PRINCIPAL,"Doy orden de inicio: Chancho Va");
	int numeroRonda = 1;
	string nombreArchivoGanador = ARCHIVO_FIFO_CHANCHO_GANADOR;
	vector<string> jugadores;

	while (!this->terminado) {
		jugadores.clear();
		string mensaje = "Empieza la ronda " + Util().itoa(numeroRonda);
		logManager.logMessage(PROCESO_PRINCIPAL, mensaje);
		this->empezarRonda();

		char jugadorGanador[BUFFSIZE];
		Fifo fifoGanador (nombreArchivoGanador.c_str());
		string sNumJugadoresGanadores;

		if (this->cantJugadores == MANOS) {
			// caso especial
			int cantGan = 0;
			while (cantGan < this->cantJugadores) {
				char jugadorGanador[BUFFSIZE];
				int bytesLeidos = fifoGanador.leer(jugadorGanador, BUFFSIZE);
				jugadorGanador[bytesLeidos] = '\0';
				sNumJugadoresGanadores += jugadorGanador;
				sNumJugadoresGanadores += SEPARADOR;
				cantGan =  Util().split(sNumJugadoresGanadores, SEPARADOR).size();
			}
		} else {
			for (int i = 0; i < this->cantJugadores; i++) {
				int bytesLeidos = fifoGanador.leer(jugadorGanador, BUFFSIZE);
				jugadorGanador[bytesLeidos] = '\0';
				sNumJugadoresGanadores += jugadorGanador;
			}
			sNumJugadoresGanadores += SEPARADOR;
		}
		fifoGanador.cerrar ();
		fifoGanador.eliminar();

		vector <string> vJugadoresGanadores = Util().split(sNumJugadoresGanadores, SEPARADOR);

		mensaje.clear();

		mensaje = "El jugador[" + vJugadoresGanadores[0] + "] hizo chancho";

		logManager.logMessage(PROCESO_PRINCIPAL, mensaje);

		for (int i = 0; i < (int)vJugadoresGanadores.size(); i++) {
			jugadores.push_back(vJugadoresGanadores[i]);
		}

		int cantGanadores = vJugadoresGanadores.size();

		if (cantGanadores < this->cantJugadores) {
			this->avisarChancho(vJugadoresGanadores);

			int cantPerdedores = this->cantJugadores - cantGanadores;
			string nombreArchivoChancho = ARCHIVO_FIFO_CHANCHO_PERDEDOR;
			Fifo fifoChancho(nombreArchivoChancho.c_str());
			string sNumJugadores;
			int cant = 0;

			while (cant < cantPerdedores) {
				char buffer [BUFFSIZE];
				int bytesLeidos = fifoChancho.leer(buffer,BUFFSIZE);
				buffer[bytesLeidos] = '\0';
				sNumJugadores += buffer;
				sNumJugadores += SEPARADOR;
				cant =  Util().split(sNumJugadores, SEPARADOR).size();
			}
			fifoChancho.cerrar ();
			fifoChancho.eliminar();

			// agrego a los perdedores
			vector <string> vJugadores = Util().split(sNumJugadores, SEPARADOR);
			for (int i = 0; i < cant; i++) {
				jugadores.push_back(vJugadores[i]);
			}
		}
		this->tablero->escribirTablero(jugadores[jugadores.size()-1]);
		if (this->tablero->hayPerdedor()){
			this->terminado = true;
		}

		mensaje = "Las manos fueron apoyadas en el siguiente orden:";
		for (int i = 0; i < (int)jugadores.size(); i++) {
			mensaje += " " + jugadores[i];
		}
		logManager.logMessage(PROCESO_PRINCIPAL, mensaje);

		numeroRonda++;

		for (int i = 0; i < cantGanadores; i++) {
			int pos = atoi(vJugadoresGanadores[i].c_str()) - 1;
			waitpid(this->pidJugadores[pos],NULL,0);

		}
	}
}

void Juego::empezarRonda(){
	string pathConstructorJugadores = PATH_CONSTRUCTOR_JUGADORES;
	int pid;
	int jugadoresCreados = 0;
	Semaforo semInicio ( (char*)SEMAFORO_INICIO,0 );
	Semaforo semChanchoVa ( (char*)SEMAFORO_CHANCHO_VA,0 );
	string semIdInicio = Util().itoa(semInicio.getId());
	string semIdChanchoVa = Util().itoa(semInicio.getId());
	string modoDebug = Util().itoa(this->modoDebug);

	// En cada nueva ronda tengo que resetear los pids de los jugadores
	this->pidJugadores.clear();

	// Creacion de Jugadores
	while ( (jugadoresCreados < this->cantJugadores) ) {
		jugadoresCreados++;
		pid = fork();

		if ( pid == 0 ){
			string sJugador = Util().itoa(jugadoresCreados);
			string sCantJugadores = Util().itoa(this->cantJugadores);
			execl(pathConstructorJugadores.c_str(),"ConstruirJugador", sJugador.c_str(), sCantJugadores.c_str(),
					semIdInicio.c_str(), semIdChanchoVa.c_str(), modoDebug.c_str(), (char*)0);

			cout << "ERROR: Archivo " << pathConstructorJugadores << "no encontrado al hacer el exec" << endl;
		}
		this->pidJugadores.push_back(pid);
	}

	logManager.logMessage(PROCESO_PRINCIPAL,"Mezclo las cartas para repartir");

	repartirCartas();

	for (int i = 0; i < this->cantJugadores; i++) {
		semInicio.v();
	}
	semInicio.eliminar();
	logManager.logMessage(PROCESO_PRINCIPAL,"Esperando hasta que algun jugador tengo chancho");
}

int Juego::obtenerNumeroDeCarta(int carta) {
	if ((carta % this->cantJugadores) != 0)
		return carta % this->cantJugadores;
	return this->cantJugadores;
}

void Juego::mezclarCartas() {
	int mazo[this->cantCartas];

	for (int i = 0; i < this->cantCartas; i++)
		mazo[i] = i + 1;

	for (int i = 0; i < this->cantCartas; i++ ) {
		int j = rand() % this->cantCartas;
		int temp = mazo[ i ];
		mazo[ i ] = mazo[ j ];
		mazo[ j ] = temp;
	}

	int k = 0;

	for (int i = 0; i < this->cantJugadores; i++) {
		string cartas;

		for (int j = k; j <  (k+CARTAS_PARTIDA); j++) {
			cartas += Util().itoa(obtenerNumeroDeCarta(mazo[j]));
			cartas += SEPARADOR;
		}
		k += CARTAS_PARTIDA;
		this->cartas.push_back(cartas);
	}
}

void Juego::repartirCartas() {
	this->mezclarCartas();

	for (int i = 0; i < this->cantJugadores; i++) {
		string nombreArchivo = ARCHIVO_FIFO;
		nombreArchivo += Util().itoa(i + 1);

		Fifo manoInicial(nombreArchivo.c_str());

		manoInicial.escribir ( (char*) this->cartas[i].c_str(), this->cartas[i].size() );

		string mensaje = "Reparto las cartas " + this->cartas[i] + " al jugador [" + Util().itoa(i+1) + "]";
		logManager.logMessage(PROCESO_PRINCIPAL,mensaje);

		manoInicial.cerrar ();
		manoInicial.eliminar ();
	}
}

void desordenar(int v[], int n){
	bool usado[n];
	int res[n];

	for (int i=0; i < n; i++){
	    usado[i] = false;
	}

	int index=0;
	for (int i=0; i < n; i++){
	    do{
	    	index = (rand() % n);
	    } while (usado[index]);
	    res[i] = v[index];
	    usado[index]=true;
	}

	for (int i=0; i < n; i++){
		v[i] = res[i];
	}
}

void Juego::avisarChancho(vector <string> vGanadores) {
	logManager.logMessage(PROCESO_PRINCIPAL, "Envio señal de chancho a los jugadores");
	// Necesario para desordenar
	int cantPerdedores = this->cantJugadores - (int)vGanadores.size();
	int perdedores[cantPerdedores], index = 0;
	memset(perdedores, 0, cantPerdedores);
	// Agrego perdedores para mandarles señal
	for (int i = 0; i < this->cantJugadores; i++) {
		bool perdio = true;
		for (int j = 0; j < (int)vGanadores.size(); j++) {
			if (atoi(vGanadores[j].c_str()) == (i+1)){
				perdio = false;
				break;
			}
		}
		if (perdio) {
			perdedores[index] = this->pidJugadores[i];
			index++;
		}
	}
	// Mando señal en desorden para no darle siempre la ventaja a uno
	desordenar(perdedores, cantPerdedores);
	for (int k=0; k < cantPerdedores; k++){
		kill(perdedores[k], SIGINT);
	}
}

Juego::~Juego() {
	delete(this->tablero);
	logManager.logMessage(PROCESO_PRINCIPAL, "Fin del juego");
}
