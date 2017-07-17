#include "LockFile.h"

LockFile::LockFile(const char* nombre, int tamanio) {

	strcpy(this->nombre, nombre);

	this->fl.l_type = F_WRLCK;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = tamanio;
	this->fl.l_pid = getpid();
	this->fd = open(this->nombre, O_CREAT | O_RDWR, 0777);
}

int LockFile::tomarLockEscritura(bool blocking) {
	this->fl.l_type = F_WRLCK;
	return this->tomarLock(blocking);

}

int LockFile::tomarLockLectura(bool blocking) {
	this->fl.l_type = F_RDLCK;
	return this->tomarLock(blocking);

}

int LockFile::tomarLock(bool blocking) {
	int resultado;
	if (blocking) {
		resultado = fcntl(this->fd, F_SETLKW, &(this->fl));
	} else
		resultado = fcntl(this->fd, F_SETLK, &(this->fl));
	return resultado;
}

int LockFile::liberarLock() {
	this->fl.l_type = F_UNLCK;
	int resultado = fcntl(this->fd, F_SETLK, &(this->fl));
	return resultado;
}

int LockFile::escribir(char* buffer, int buffsize) {
	lseek(this->fd, this->fl.l_start, SEEK_SET);
	int resultado = write(this->fd, buffer, buffsize);
	return resultado;
}
int LockFile::leer(char* buffer, int buffsize) {
	lseek(this->fd, this->fl.l_start, SEEK_SET);
	int resultado = read(this->fd, buffer, buffsize);
	return resultado;
}

void LockFile::setPosicionLock(int posicionRelativa) {
	this->fl.l_start = posicionRelativa;
}

LockFile::~LockFile() {
	close(this->fd);
}
