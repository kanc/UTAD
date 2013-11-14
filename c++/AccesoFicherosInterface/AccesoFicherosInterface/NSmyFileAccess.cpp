#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "NSmyFileAccess.h"
#include "IMyFileAccess.h"
	

//***** Abre un fichero y lo añade a nuestra tabla de ficheros abiertos
unsigned int MyFileAccess::OpenFile(const char *filename, int mode)
{
	const char *tipofile;
	IMyFileAccess::fileType *fichero;

	if (OPENEDFILES < MAXFILES)
	{
		//convertimos nuestro tipo a un tipo reconocible por fopen
		tipofile=MyFileAccess::CastOpenMode(mode);

		//abrimos el fichero con el modo indicado
		FILE *myFile=fopen(filename,tipofile);

		if (myFile !=NULL)
		{
			//aumentamos la varible que nos indica los ficheros abiertos
			OPENEDFILES++;

			//asignamos el puntero devuelto en la siguiente casilla libre de nuestra tabla global
			mvar_Files[OPENEDFILES-1]=myFile;

			//creamos un objeto de nuestro tipo y usamos la direccion de memoria como id
			return (int)myFile;
		}
		else
			return 0;		
	}
	else
		return 0;

}

//***** cierra un fichero y elimina la referencia de nuestra tabla de ficheros abiertos
bool MyFileAccess::CloseFile(unsigned int idFile)
{		
	FILE *fichero=NULL;
	int posFile=-1;

	//buscamos la posicion del fichero en la tabla de punteros a fichero
	posFile=searchFile(idFile);

	if (posFile >= 0)
	{	
		//cogemos el puntero al fichero de la tabla
		fichero=mvar_Files[posFile];

		//cerramos el fichero y si todo ha ido ok ponemos a null la posicion de la tabla donde estaba el puntero y restamos el numero de ficheros abiertos
		if (fclose(fichero) == 0)
		{
			mvar_Files[posFile]=NULL;
			OPENEDFILES--;

			return true;
		}
		else
			return false;
	}


}

//***** lee de "file" numero de caracteres indicado como parametro en "numChars" almacenandolo en el parametro "Buffer" y devuelve los caracteres leidos
unsigned int MyFileAccess::ReadFile(unsigned int idFile, char *buffer, unsigned int numChars)
{
	char c;
	int leidos=0;
	FILE *fichero=NULL;
	int posFile=-1;

	//buscamos la posicion del fichero en la tabla de punteros a fichero
	posFile=searchFile(idFile);

	if (posFile >= 0)
	{	
		//cogemos el *file de la tabla
		fichero=mvar_Files[posFile];

		//leemos los caracters indicados por el usuario
		for (unsigned int i=0;i<numChars;i++)
		{
			//leemos el caracter haciendo casting de int a char
			c=(char)getc(fichero);

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

//****** Escribe en un fichero los caracteres pasados en "Buffer" y devuelve el numero de caracteres escritos
unsigned int MyFileAccess::WriteFile(unsigned int idFile, const char *buffer)
{
	char c=1;
	int carsEscritos=0;
	FILE *fichero=NULL;
	int posFile=-1;

	//buscamos la posicion del fichero en la tabla de punteros a fichero
	posFile=searchFile(idFile);

	if (posFile >= 0)
	{	
		//cogemos el *file de la tabla
		fichero=mvar_Files[posFile];

		//escribimos los caracteres pasados en buffer hasta que se acabe la cadena o haya algun error al escribir en el fichero
		while (c != '\0' && c != EOF)
		{
			//cogemos el caracter a donde apunta el puntero
			c=*buffer;

			//guardamos en el fichero
			fputc((int)c,fichero);
			carsEscritos++;

			//pasamos a la siguiente posicion en memoria
			buffer++;
		}
	}

	return carsEscritos;
}

//******* devuelve el numero de apariciones de una cadena en un fichero
unsigned int MyFileAccess::StringInFile(const char *search, unsigned int idFile)
{
	int apariciones=0;
	int lngCadena=0;
	char *textoFichero=new char[1000];
	const char *posicionCadena=NULL;

	//aqui texto fichero apunta al inicio del texto del fichero
	MyFileAccess::ReadAllFile(idFile,textoFichero);	

	//obtenemos la longuitud de la cadena
	lngCadena=MyFileAccess::StringLenght(search);

	do 	
	{	//ahora textofichero apunta a la posicion de la primera aparicion de la cadena asi que seguimos buscando a partir de ahi
		textoFichero=strstr(textoFichero,search);		
		
		if (textoFichero!=NULL)
		{	apariciones++;
			//avanzamos el puntero la longuitud de la cadena para que siga buscando a partir de ahi
			textoFichero+=lngCadena;
		}
	}
	while (textoFichero!=NULL);

	return apariciones;

}

//***** mete el un puntero a char pasado como parametro el contenido del fichero
void MyFileAccess::ReadAllFile(unsigned int idFile, char *texto)
{
	char c=1;
	FILE *fichero=NULL;
	int posFile=-1;

	//buscamos la posicion del fichero en la tabla de punteros a fichero
	posFile=searchFile(idFile);

	if (posFile >= 0)
	{	
		//cogemos el *file de la tabla
		fichero=mvar_Files[posFile];

		//colocamos el cursor al principio del fichero
		rewind(fichero);

		//leemos todos los caracteres del fichero y los guardamos en memoria
		while (c != EOF)
		{
			c=(char)getc(fichero);
			*texto=c;
			texto++;
		}
	}

	*texto='\0';
}

//*******Devuelve un entero con la longuitud de una cadena
unsigned int MyFileAccess::StringLenght(const char *cadena)
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

const char * MyFileAccess::CastOpenMode(int mode)
{	
	char *type;

	switch (mode)
	{
		case 0: //read
			type=(char *)malloc(1);
			*type='r';
			break;

		case 1: //write
			type=(char *)malloc(1);
			*type='w';
			break;

		case 2: //readwrite
			type=(char *)malloc(2);
			*type='r';
			type++;
			*type='+';
			break;
	}

	return type;
}

int MyFileAccess::searchFile(unsigned int idFile)
{
	int posTabla=-1;

	//recorremos nuestra tabla de ficheros
	for (int i=0;i<MAXFILES;i++)
	{
		//buscamos en nuestra tabla la direccion de memoria correspondiente al id del fichero
		if ((int)&mvar_Files[i]==idFile)
		{
			posTabla=i;
			break;
		}
	}

	return posTabla;
}

IMyFileAccess::fileType * createObject(unsigned int idFile, const char *filename)
{
	/*IMyFileAccess::fileType *fichero=new(IMyFileAccess::fileType);

	fichero->filename=filename;
	fichero->idFile=idFile;

	return fichero;*/

	return NULL;

}