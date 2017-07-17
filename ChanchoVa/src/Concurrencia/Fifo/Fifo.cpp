#include "Fifo.h"
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

Fifo :: Fifo ( const char* nombre ) {

	strcpy ( this->nombre,nombre );
	// se crea el fifo
	int error = mknod ( nombre,S_IFIFO|0666,0 );

	//if (error == -1) cout << "MIRA QUE EL FIFO YA ESTABA CREADO" << endl;
	error++;
	// se inicializa el descriptor en -1
	this->fileDes = -1;
}

Fifo :: ~Fifo () {
}

int Fifo :: escribir ( char* dato,int datoSize ) {

	// se abre el file descriptor para escritura
	if ( this->fileDes == -1) {

		//cout<<getpid() << "Escritor: esperando abrir el fifo" << endl;

		this->fileDes = open ( this->nombre,O_WRONLY );

		//cout<<getpid() << "Escritor: fifo abierto" << endl;
	}

	// se escriben los datos en el fifo
	int resultado = write ( this->fileDes,(const void *)dato,datoSize );

	return resultado;
}

int Fifo :: leer ( char* buffer,int buffSize ) {

	// se abre el file descriptor para lectura
	if ( this->fileDes == -1 ) {

		//cout << "Lector: esperando abrir el fifo" << endl;

		this->fileDes = open ( this->nombre,O_RDONLY );

		//cout << "Lector: fifo abierto" << endl;
	}

	// se leen los datos del fifo
	//cout << "Lector: esperando lectura" << endl;

	int resultado = read ( this->fileDes,(void *)buffer,buffSize );

	return resultado;
}

void Fifo :: cerrar () {
	close ( this->fileDes );
}

void Fifo :: eliminar () {
	unlink ( this->nombre );
}

int Fifo :: getFileDescriptor() {
	return this->fileDes;
}
