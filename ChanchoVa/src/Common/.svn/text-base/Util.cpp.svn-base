#include "Util.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

string Util::itoa(int number){
	 string numberString;
	 stringstream conversor;
	 conversor << number;
	 numberString = conversor.str();
	 return numberString;
}

vector<string> Util::split(string cadena , char separator){

	vector<string> resultado;
	size_t encontrado;
	int inicio = 0;

	encontrado=cadena.find_first_of(separator);
	while (encontrado!=string::npos) {
		string termino = cadena.substr(inicio,encontrado - inicio);

		if (termino.size()) {
			resultado.push_back(termino);
		}
	    inicio = encontrado + 1;
	    encontrado=cadena.find_first_of(separator,encontrado+1);
	}

	return resultado;

}

