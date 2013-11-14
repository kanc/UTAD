// AccesoFicherosNamespace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NSmyFileAccess.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char *texto=new (char);	
	char *nuevoTexto=" esto es un nuevo fragmento escrito";
	int numLeidos=0;
	FILE *ficheroLeeYEscribe=MyFileAccess::OpenFile("test.txt","r+"); //lo abrimos para lectura y escritura
	FILE *ficheroLee=MyFileAccess::OpenFile("test2.txt","r"); //lo abrimos para lectura

	if (ficheroLee!=NULL && ficheroLeeYEscribe!=NULL)

	{	numLeidos=MyFileAccess::ReadFile(ficheroLeeYEscribe,texto,60);
		printf("texto leido fichero 1: %s cars. leidos: %i",texto,numLeidos);
		getchar();

		numLeidos=MyFileAccess::ReadFile(ficheroLee,texto,50);
		printf("\ntexto leido fichero 2: %s cars. leidos: %i",texto,numLeidos);
		getchar();	
	
		//escribimos en el fichero
		MyFileAccess::WriteFile(ficheroLeeYEscribe,nuevoTexto);

		printf("apariciones de 'es' en fichero 1: %i",MyFileAccess::StringInFile("es",ficheroLeeYEscribe));
		getchar();

		MyFileAccess::CloseFile(ficheroLee);
		MyFileAccess::CloseFile(ficheroLeeYEscribe);

		texto=NULL;
		delete (texto);
	}
	else
		printf("Los ficheros no existen");
		getchar();

	return 0;
}
