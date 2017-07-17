#ifndef LOCKFILE_H_
#define LOCKFILE_H_

#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>

class LockFile {

private:

	struct flock fl;
	int fd;
	char nombre [ 255 ];
	int tomarLock(bool blocking);

public:

	LockFile ( const char* nombre, int tamanio );
	virtual ~LockFile();

	int tomarLockEscritura (bool blocking);
	int tomarLockLectura (bool blocking);
	int liberarLock ();
	int escribir ( char* buffer,int buffsize );
	int leer (char* buffer,int buffsize);
	void setPosicionLock (int posicionRelativa);
};

#endif /* LOCKFILE_H_ */
