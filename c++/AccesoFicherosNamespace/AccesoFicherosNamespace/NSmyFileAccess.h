//Fichero de cabecera donde tenemos declaradas las funciones de myFileAccess.cpp y las variables globales
namespace MyFileAccess {

	#include <stdio.h>
	#include <string.h>

	FILE * OpenFile(const char *filename, const char *mode);
	bool CloseFile(FILE *file);
	int ReadFile(FILE * file, char *buffer, int numChars);
	int WriteFile(FILE *file, const char *buffer);
	int StringInFile(const char *string, FILE *file);
	void ReadAllFile(FILE *file, char *texto);
	int longuitudCadena(const char *cadena);
};