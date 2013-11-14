#include "stdafx.h"
#include "MyFileAccessImp.h"
#include <string.h>

MyFileAccessImp::MyFileAccessImp()
{
	mvar_File=NULL;
}

MyFileAccessImp::~MyFileAccessImp()
{
	delete mvar_File;
}

bool MyFileAccessImp::OpenFile(const char *filename, int mode)
{
	char *tipofile=new char[3];	

	//convertimos nuestro tipo a un tipo reconocible por fopen
	CastOpenMode(mode,tipofile);

	//abrimos el fichero con el modo indicado
	mvar_File=fopen(filename,tipofile);

	delete[] tipofile;

	if (mvar_File !=NULL)
		return true;	
	else
		return false;		
}

bool MyFileAccessImp::CloseFile()
{
	if (fclose(mvar_File) == 0)	
		return true;
	
	else
		return false;
}

unsigned int MyFileAccessImp::ReadFile(char *buffer, unsigned int numChars, bool inicioFichero)
{
	char c;
	int leidos=0;		

	if (mvar_File !=NULL)
	{	
		if (inicioFichero)
			rewind(mvar_File);

		//leemos los caracters indicados por el usuario
		for (unsigned int i=0;i<numChars;i++)
		{
			//leemos el caracter haciendo casting de int a char
			c=(char)getc(mvar_File);

			//si no es el fin de fichero
			if (c != EOF)
			{
				//guardamos el contenido donde apunta el puntero, pasamos a la siguiente direccion de memoria e incrementamos los caracteres leidos
				*buffer=c;
				buffer++;
				leidos++;
			}
			else
				break;		
		}

		//metemos el caracter de fin de cadena
		*buffer='\0';
	}
	return leidos;
}

unsigned int MyFileAccessImp::WriteFile(const char *buffer)
{
	char c=1;
	int carsEscritos=0;	

	if (mvar_File!=NULL)
	{	
		//escribimos los caracteres pasados en buffer hasta que se acabe la cadena o haya algun error al escribir en el fichero
		while (c != '\0' && c != EOF)
		{
			//cogemos el caracter a donde apunta el puntero
			c=*buffer;

			//guardamos en el fichero
			fputc((int)c,mvar_File);
			carsEscritos++;

			//pasamos a la siguiente posicion en memoria
			buffer++;
		}
	}

	return carsEscritos;
}

unsigned int MyFileAccessImp::StringInFile(const char *string){
	int apariciones=0;
	int lngCadena=0;
	char *textoFichero=new char[1000];
	const char *posicionCadena=NULL;

	//aqui texto fichero apunta al inicio del texto del fichero
	MyFileAccessImp::ReadAllFile(textoFichero);	

	//obtenemos la longuitud de la cadena
	lngCadena=MyFileAccessImp::StringLength(string);

	do 	
	{	//ahora textofichero apunta a la posicion de la primera aparicion de la cadena asi que seguimos buscando a partir de ahi
		textoFichero=strstr(textoFichero,string);		
		
		if (textoFichero!=NULL)
		{	apariciones++;
			//avanzamos el puntero la longuitud de la cadena para que siga buscando a partir de ahi
			textoFichero+=lngCadena;
		}
	}
	while (textoFichero!=NULL);

	return apariciones;
}

void MyFileAccessImp::ReadAllFile(char *texto)
{
	char c=1;

	if (mvar_File!=NULL)
	{	
		//colocamos el cursor al principio del fichero
		rewind(mvar_File);

		//leemos todos los caracteres del fichero y los guardamos en memoria
		while (c != EOF)
		{
			c=(char)getc(mvar_File);
			*texto=c;
			texto++;
		}
	}

	*texto='\0';
}

unsigned int MyFileAccessImp::StringLength(const char *cadena) const
{
	int longuitud=0;
	char c;

	if (cadena==NULL)
		return 0;
	else
	{	c=*cadena;

		while (c != '\0')
		{			
			cadena++;
			longuitud++;
			c=*cadena;
		}
		return longuitud;
	}
}

void MyFileAccessImp::CastOpenMode(unsigned int mode, char * type) const
{		
	switch (mode)
	{
		case 0: //read
			type=(char *)realloc(type,sizeof(char)*2);
			*type='r';
			type++;
			*type='\0';

			break;

		case 1: //write
			type=(char *)realloc(type,sizeof(char)*2);
			*type='w';
			type++;
			*type='\0';

			break;

		case 2: //readwrite
			type=(char *)realloc(type,sizeof(char)*3);
			*type='r';
			type++;
			*type='+';
			type++;
			*type='\0';

			break;
	}

}