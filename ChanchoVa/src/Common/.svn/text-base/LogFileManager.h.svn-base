#ifndef LOGFILEMANAGER_H_
#define LOGFILEMANAGER_H_

#include <string>
#include <fstream>
#include <time.h>
#include <iostream>
#include <sstream>
#include "Util.h"
#include "Constants.h"
#include "../Concurrencia/Locks/LockFile.h"

#define AMARILLO 33	
#define VERDE 32 	
#define ROJO 31		
#define AZUL 34
#define MAGENTA 35
#define CYAN 36
#define NEGRO 00	//Normal


using namespace std;


class LogFileManager {

private:
	string fileName;
	string pid;
	LockFile lock;
	bool debug;
	string colorizar (string tipoProceso, string msj);

public:
	LogFileManager();
	virtual ~LogFileManager();
	void vaciarLog();
	void setDebugMode(bool);
	void logMessage (string tipoProceso, string msj);

};

#endif /* LOGFILEMANAGER_H_ */
