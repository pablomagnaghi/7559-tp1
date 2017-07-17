#include "TableroPuntaje.h"

TableroPuntaje::TableroPuntaje(int cantJugadores, string filename): lock(filename.c_str(),sizeof(char)) {
	this->cantidadJugadores = cantJugadores;
	this->fileName = filename;
	for (int i = 0; i < this->cantidadJugadores; i++){
		this->puntajes.push_back(0);
	}
}

void TableroPuntaje::escribirTablero(string ultimoJugador){
	string sChancho(TABLERO_CHANCHO);
	int jugador = atoi(ultimoJugador.c_str());
	if (this->puntajes[jugador-1] < (int) sChancho.size()){
		this->puntajes[jugador-1]++;
	}
	actualizarArchivoPuntajes();
}

void TableroPuntaje::actualizarArchivoPuntajes(){
	string sPuntajes;
	string sChancho(TABLERO_CHANCHO);
	sPuntajes += "\nPuntajes\n";
	sPuntajes += "-------------------------\n";

	for (int i = 0; i < this->cantidadJugadores; i++){
		sPuntajes += "Jugador " + Util::itoa(i+1) + ": ";
		for (int j=0; j < this->puntajes[i]; j++){
			sPuntajes += sChancho[j];
		}
		if (this->puntajes[i] >= (int) sChancho.size()){
			sPuntajes += " (PERDIO)";
		}
		sPuntajes += "\n";
	}
	sPuntajes += "-------------------------\n";

	lock.tomarLockEscritura(true);
	fstream fileOut;
	fileOut.open(fileName.c_str() , fstream::out | fstream::trunc);
	fileOut << sPuntajes;
	fileOut.close();
	lock.liberarLock();
}

bool TableroPuntaje::hayPerdedor(){
	string sChancho(TABLERO_CHANCHO);
	for (int i = 0; i < this->cantidadJugadores; i++){
		if (this->puntajes[i] == (int)sChancho.size()){
			return true;
		}
	}
	return false;
}

string TableroPuntaje::mostrarTablero(string filename){
	string resultado("");
	string linea("");
	fstream file;
	LockFile lock(filename.c_str(),sizeof(char));

	lock.tomarLockLectura(true);
	file.open(filename.c_str() , fstream::in);
	while (!file.eof()){
		getline(file,linea);
		resultado += linea + '\n';
	}

	file.close();
	lock.liberarLock();
	return resultado;
}

TableroPuntaje::~TableroPuntaje() {
}
