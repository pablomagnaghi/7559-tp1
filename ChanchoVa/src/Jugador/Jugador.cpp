#include "Jugador.h"

Jugador::Jugador(char** argv){
	this->pidString = Util().itoa(getpid());
	this->numJugador = atoi(argv[1]);
	this->cantJugadores = atoi(argv[2]);
	this->modoDebug = atoi(argv[5]);
	this->cartas = new int[4];
	this->logManager.setDebugMode(this->modoDebug);

	this->inicializarCartas();

	this->numJugadorIzquierda = obtenerJugadorIzquierda(atoi(argv[2]));
	this->numJugadorDerecha = obtenerJugadorDerecha(atoi(argv[2]));

	this->nombre = "Jugador [" + Util().itoa(this->numJugador) + "]";
	this->tengoChancho = false;
	this->posicionCartaEnviada = 0;

	this->semIdInicio = atoi(argv[3]);
	this->semIdChanchoVa = atoi(argv[4]);

	// todo
	//string mensaje = this->nombre + ": Hola soy un Jugador";
	//logManager.logMessage(PROCESO_JUGADOR, mensaje);
}

void Jugador::inicializarCartas() {
	for(int i=0;i<=CARTAS_PARTIDA;i++){
		this->cartas[i] = 0;
	}
}

// Determino de que jugador tiene que recibir las cartas
int Jugador::obtenerJugadorIzquierda(int cantJugadores) {
	if (this->numJugador == 1) {
		return cantJugadores;
	}
	return (this->numJugador - 1);
}

// Determino a que jugador tiene que enviar las cartas
int Jugador::obtenerJugadorDerecha(int cantJugadores) {
	if (this->numJugador == cantJugadores) {
		return 1;
	}
	return (this->numJugador + 1);
}

void Jugador::jugar() {
	SIGINT_Handler sigint_handler;
	SignalHandler :: getInstance()->registrarHandler( SIGINT, &sigint_handler );
	Semaforo semInicio ( semIdInicio );
	Semaforo semChanchoVa ( semIdChanchoVa );
	string mensaje;
	string nombreArchivoCartaRecibida = ARCHIVO_FIFO_CARTA_RECIBIDA;
	nombreArchivoCartaRecibida += Util().itoa(this->numJugador);
	char cartaRecibida[ BUFFSIZE ];
	int pid;
	int cartaParaEnviar;
	string modoDebug = Util().itoa(this->modoDebug);

	sigint_handler.setNumJugador(this->numJugador);

	esperarInicio(semIdInicio);
	this->tengoChancho = this->checkChancho();
	string nombreArchivo = ARCHIVO_FIFO_CHANCHO_VERIFICAR;;

	int ronda = 0;

	while ( sigint_handler.getGracefulQuit() == 0 && !this->tengoChancho ) {
		ronda++;
		if (this->numJugador == JUGADOR_MANO) {
			this->avisarLaMano();
			for (int i = 1; i < this->cantJugadores; i++)
				semChanchoVa.v();
		} else {
			this->conocerLaMano();
			semChanchoVa.p();
		}
		semChanchoVa.eliminar();

		cartaParaEnviar = obtenerCartaParaenviar();
		string sJugador = Util().itoa(this->numJugador);

		this->pidHijos.clear();

		pid = fork();
		if ( pid == 0 ) {
			string pathConstructorManoEnviadora = PATH_CONSTRUCTOR_MANO_ENVIADORA;
			string sJugadorDerecha = Util().itoa(this->numJugadorDerecha);
			string sCartaParaEnviar = Util().itoa(cartaParaEnviar);
			execl(pathConstructorManoEnviadora.c_str(),"ConstruirManoEnviadora", sJugador.c_str(),
					sJugadorDerecha.c_str(), sCartaParaEnviar.c_str(), modoDebug.c_str(), (char*)0);
			cout << "ERROR: Archivo " << pathConstructorManoEnviadora << "no encontrado al hacer el exec" << endl;
		}

		this->pidHijos.push_back(pid);

		pid = fork();
		if ( pid == 0 ) {
			string pathConstructorManoReceptora = PATH_CONSTRUCTOR_MANO_RECEPTORA;
			string sJugadorIzquierda = Util().itoa(this->numJugadorIzquierda);
			execl(pathConstructorManoReceptora.c_str(),"ConstruirManoReceptora", sJugador.c_str(),
					sJugadorIzquierda.c_str(), Util().itoa(ronda).c_str(), modoDebug.c_str(), (char*)0);
			cout << "ERROR: Archivo " << pathConstructorManoReceptora << "no encontrado al hacer el exec" << endl;
		}

		this->pidHijos.push_back(pid);

		// Espero hasta recibir una carta
		Fifo fifoCartaRecibida (nombreArchivoCartaRecibida.c_str());
		sigint_handler.setPidsHijos(this->pidHijos[0], this->pidHijos[1]);
		int bytesLeidos = fifoCartaRecibida.leer(cartaRecibida, BUFFSIZE);
		cartaRecibida[bytesLeidos] = '\0';
		this->cartas[this->posicionCartaEnviada] = atoi(cartaRecibida);
		fifoCartaRecibida.cerrar ();
		// todo
		//mostrarMensajeDeCartas(Util().itoa(ronda));
		wait(NULL);
		wait(NULL);
		this->tengoChancho = this->checkChancho();
	}

	if (this->tengoChancho) {
		//ronda++;
		this->apoyarMano();
		semChanchoVa.eliminar();
	}

	SignalHandler :: destruir();
}

void Jugador::esperarInicio(int semIdInicio){
	Semaforo semInicio ( semIdInicio );

	// todo
	//string mensaje = this->nombre + ": Termine de inicializar y estoy esperando para comenzar la ronda";
	//logManager.logMessage(PROCESO_JUGADOR,mensaje);

	leerCartasIniciales();
	semInicio.p();

	// todo
	//mensaje = this->nombre + ": Empiezo a jugar!";
	//logManager.logMessage(PROCESO_JUGADOR, mensaje);
}

void Jugador::leerCartasIniciales() {
	string nombreArchivo = ARCHIVO_FIFO;
	nombreArchivo += Util().itoa(this->numJugador);

	Fifo manoInicial(nombreArchivo.c_str());

	char cartas [ BUFFSIZE ];
	int bytesLeidos = manoInicial.leer ( cartas,BUFFSIZE );
	cartas[bytesLeidos] = '\0';

	string sCartas = cartas;
	obtenerCartasIniciales(sCartas);
	manoInicial.cerrar ();
}

void Jugador::obtenerCartasIniciales(string cartas) {
	for (int i = 0; i < CARTAS_PARTIDA; i++){
		this->cartas[i] = atoi(Util().split(cartas, SEPARADOR)[i].c_str());
	}

	string mensaje =  this->nombre + ": Mis cartas iniciales son las cartas son: ";
	for (int i = 0; i < CARTAS_PARTIDA; i++) {
		mensaje += " " + Util().itoa(this->cartas[i]);
	}
	// todo
	//logManager.logMessage(PROCESO_JUGADOR,mensaje);
}

bool Jugador::checkChancho(){
	if((this->cartas[0] == this->cartas[1]) && (this->cartas[0] == this->cartas[2]) && (this->cartas[0] == this->cartas[3]) ){
		return true; //tres iguales, tengo chancho
	}
	return false;
}

int Jugador::obtenerCartaParaenviar(){
	int primera = this->cartas[0];
	int segunda = this->cartas[1];
	int tercera = this->cartas[2];
	int cuarta = this->cartas[3];

	if(primera!= segunda && primera != tercera && primera!= cuarta)
		this->posicionCartaEnviada = 0;

	if(primera!= segunda && primera != tercera && primera == cuarta)
		this->posicionCartaEnviada = (rand() % 2) + 1;

	if(primera!= segunda && primera == tercera && primera != cuarta){
		if (rand() %  2 == 1 )
			this->posicionCartaEnviada = 1;
		else
			this->posicionCartaEnviada = 3;
	}
	if(primera == segunda && primera != tercera && primera != cuarta)
		this->posicionCartaEnviada = (rand() % 2) + 2;

	if(primera != segunda && primera == tercera && primera == cuarta)
		this->posicionCartaEnviada = 1; //tres iguales, descarto la otra

	if(primera == segunda && primera != tercera && primera == cuarta)
		this->posicionCartaEnviada = 2; //tres iguales, descarto la otra

	if(primera == segunda && primera == tercera && primera != cuarta)
		this->posicionCartaEnviada = 3; //tres iguales, descarto la otra

	return this->cartas[this->posicionCartaEnviada];
}

void Jugador::apoyarMano() {
	// Apoyo la mano
	string nombreArchivoChancho = ARCHIVO_FIFO_CHANCHO_GANADOR;
	Fifo fifoGanador(nombreArchivoChancho.c_str());

	string sNumJugador;
	sNumJugador =+ SEPARADOR;
	sNumJugador += Util::itoa(this->numJugador);

	fifoGanador.escribir((char*)sNumJugador.c_str(), sNumJugador.size());

	//string mensaje = this->nombre + ": Tengo chancho, apoye mi mano";
	//logManager.logMessage(PROCESO_JUGADOR, mensaje);
	fifoGanador.cerrar();
	//fifoGanador.eliminar();
}

void Jugador::avisarLaMano() {
	for (int i = 0; i < this->cantJugadores; i++) {
		if ((i + 1) != this->numJugador) {
			string nombreArchivo = ARCHIVO_FIFO_SOY_MANO;
			nombreArchivo += Util().itoa(i + 1);

			Fifo soyMano(nombreArchivo.c_str());

			soyMano.escribir ( (char*) this->nombre.c_str(), this->nombre.size() );

			string mensaje = "Le aviso al jugador [" + Util().itoa(i+1) + "] que soy mano";
			//logManager.logMessage(PROCESO_PRINCIPAL,mensaje);

			soyMano.cerrar ();
			soyMano.eliminar ();
		}
	}
}

void Jugador::conocerLaMano() {
	string nombreArchivo = ARCHIVO_FIFO_SOY_MANO;
	nombreArchivo += Util().itoa(this->numJugador);

	char jugadorMano[BUFFSIZE];
	Fifo soyMano(nombreArchivo.c_str());
	int bytesLeidos = soyMano.leer(jugadorMano, BUFFSIZE );
	jugadorMano[bytesLeidos] = '\0';
	string mensaje = this->nombre + ": Me entere que el " + jugadorMano + " es mano";
	//logManager.logMessage(PROCESO_JUGADOR,mensaje);
	soyMano.cerrar ();
	soyMano.eliminar ();
}

void Jugador::mostrarMensajeDeCartas(string ronda) {
	//string mensaje = this->nombre + ": El jugador " + Util::itoa(this->numJugadorIzquierda) +
	//		" me envio la carta [" + Util().itoa(this->cartas[this->posicionCartaEnviada]) + "]";

	//logManager.logMessage(PROCESO_JUGADOR, mensaje);
	string mensaje = this->nombre + ": Mis cartas en la ronda " + ronda + " son";
	for (int i = 0; i < CARTAS_PARTIDA; i++) {
		mensaje += " " + Util().itoa(this->cartas[i]);
	}
	logManager.logMessage(PROCESO_JUGADOR, mensaje);
}

Jugador::~Jugador() {
	delete this->cartas;
	//string mensaje = this->nombre + ": Termine ";
	//logManager.logMessage(PROCESO_JUGADOR,mensaje);
}

