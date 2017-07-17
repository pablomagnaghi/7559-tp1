#ifndef TABLEROPUNTAJE_H_
#define TABLEROPUNTAJE_H_

#include "../Concurrencia/Locks/LockFile.h"
#include "../Common/Constants.h"
#include "../Common/Util.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class TableroPuntaje {
public:
	TableroPuntaje(int cantJugadores, string filename);
	void escribirTablero(string jug);
	bool hayPerdedor();
	static string mostrarTablero(string filename);
	virtual ~TableroPuntaje();
private:
	int cantidadJugadores;
	string fileName;
	vector<int> puntajes;
	LockFile lock;
	void actualizarArchivoPuntajes();
};

#endif /* TABLEROPUNTAJE_H_ */
