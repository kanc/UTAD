//Fichero de cabecera donde tenemos declaradas las funciones de myFileAccess.cpp y las variables globales
#include "IMyFileAccess.h"

namespace MyFileAccess {

	const int MAXFILES=10;
	int OPENEDFILES=0;
	FILE *mvar_Files[MAXFILES];

	unsigned int OpenFile(const char *filename, int mode);
	bool CloseFile(unsigned int idFile);
	unsigned int ReadFile(unsigned int idFile, char *buffer, unsigned int numChars);
	unsigned int WriteFile(unsigned int idFile, const char *buffer);
	unsigned StringInFile(const char *search, unsigned int idFile);
	void ReadAllFile(unsigned int idFile, char *texto);
	unsigned int StringLenght(const char *cadena);
	const char * CastOpenMode(int mode);
	int searchFile(unsigned int idFile);
	IMyFileAccess::fileType * createObject(unsigned int idFile, const char *filename);
};