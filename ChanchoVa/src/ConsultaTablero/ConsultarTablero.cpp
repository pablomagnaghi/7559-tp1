#include "TableroPuntaje.h"
#include "../Common/Constants.h"

int main(int argc, char* argv[]) {
	string fileName = TABLERO_FILE_PATH;
	string result = TableroPuntaje::mostrarTablero(fileName);
	cout << result;
	return 0;
}
