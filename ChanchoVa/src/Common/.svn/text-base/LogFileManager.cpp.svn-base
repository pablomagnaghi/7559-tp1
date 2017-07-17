#include "LogFileManager.h"


LogFileManager::LogFileManager() : lock(LOG_FILE_PATH,sizeof(char)) {
	fileName = LOG_FILE_PATH;
	this->debug = false;
}

LogFileManager::~LogFileManager() {

}

void LogFileManager::vaciarLog(){
	fstream fileOut;
	fileOut.open(fileName.c_str() , ios::out | ios::in | ios::trunc );
	fileOut.close();
}

void LogFileManager::setDebugMode(bool mode){
	this->debug = mode;
}

void LogFileManager::logMessage(string tipoProceso,string msj){

	lock.tomarLockEscritura(true);	

	time_t horaActual;

	time(&horaActual );

	string msjALoguear("");
	msjALoguear += "[";
	msjALoguear += ctime(&horaActual);
	msjALoguear.erase(msjALoguear.length()-1);
	msjALoguear += "] ";	

	//todo ver con el tema de los hijos del jugador
	//msjALoguear += "[PID: ";
	//msjALoguear += pid;
	//msjALoguear += "] [";

	msjALoguear += "[";
	msjALoguear += tipoProceso;
	msjALoguear += "]		";
	msjALoguear += msj;
	msjALoguear += "\0";

	fstream fileOut;
	fileOut.open(fileName.c_str() , fstream::out | fstream::app );

	if 	(!fileOut.good())
		cout  << "ERROR: Process[" << getpid() << "] Could not open LOG file" << endl;
	fileOut << msjALoguear << endl;
	fileOut.close();
	lock.liberarLock();

	if (this->debug) {
		cout << colorizar(tipoProceso,msjALoguear) << endl;
	}
}

string LogFileManager::colorizar(string tipoProceso, string msj){

	int color;	
	if (tipoProceso.compare(PROCESO_PRINCIPAL)==0)
		color = AMARILLO;
	if (tipoProceso.compare(PROCESO_JUGADOR)==0)
		color = ROJO;
	if (tipoProceso.compare( PROCESO_MANO_ENVIADORA)==0)
		color = VERDE;
	if (tipoProceso.compare( PROCESO_MANO_RECEPTORA)==0)
		color = AZUL;

	return "\E["+Util().itoa(color)+"m"+msj+"\033[0m";
}

