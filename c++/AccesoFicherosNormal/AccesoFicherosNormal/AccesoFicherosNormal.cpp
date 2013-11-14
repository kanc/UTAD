// AccesoFicherosNormal.cpp : Defines the entry point for the conole application.
//
#include "stdafx.h"
#include "myFileAccess.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char *texto=new (char);	
	char *nuevoTexto=" esto es un nuevo fragmento escrito";
	int numLeidos=0;
	FILE *ficheroLeeYEscribe=OpenFile("test.txt","r+"); //lo abrimos para lectura y escritura
	FILE *ficheroLee=OpenFile("test2.txt","r"); //lo abrimos para lectura

	numLeidos=ReadFile(ficheroLeeYEscribe,texto,60);
	printf("texto leido fichero 1: %s cars. leidos: %i",texto,numLeidos);
	getchar();

	numLeidos=ReadFile(ficheroLee,texto,50);
	printf("\ntexto leido fichero 2: %s cars. leidos: %i",texto,numLeidos);
	getchar();	
	
	//escribimos en el fichero
	WriteFile(ficheroLeeYEscribe,nuevoTexto);

	printf("apariciones de 'es' en fichero 1: %i",StringInFile("es",ficheroLeeYEscribe));
	getchar();

	CloseFile(ficheroLee);
	CloseFile(ficheroLeeYEscribe);

	texto=NULL;
	delete (texto);

	return 0;
}

