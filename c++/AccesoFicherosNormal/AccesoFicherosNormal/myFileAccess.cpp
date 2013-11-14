#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "myFileAccess.h"

const int MAXFILES=10;
int OPENEDFILES=0;
FILE *mvar_Files[MAXFILES];

//***** Abre un fichero y lo añade a nuestra tabla de ficheros abiertos
FILE * OpenFile(const char *filename, const char *mode)
{
	if (OPENEDFILES < MAXFILES)
	{
		//abrimos el fichero con el modo indicado
		FILE *myFile=fopen(filename,mode);

		if (myFile !=NULL)
		{
			//aumentamos la varible que nos indica los ficheros abiertos
			OPENEDFILES++;
			//asignamos el puntero devuelto en la siguiente casilla libre de nuestra tabla global
			mvar_Files[OPENEDFILES-1]=myFile;
			//devolvemos el puntero a FILE
			return mvar_Files[OPENEDFILES-1];
		}
		else
			return NULL;		

	}
	else
		return NULL;

}

//***** cierra un fichero y elimina la referencia de nuestra tabla de ficheros abiertos
bool CloseFile(FILE *file)
{	
	int res=0;

	//comprobamos que no sea NULL el parametro pasado
	if (file != NULL)
	{
		//recorremos nuestra tabla de ficheros
		for (int i=0;i<MAXFILES;i++)
		{
			//buscamos el puntero en nuestra tabla que apunte a la misma direccion que el puntero pasado a la funcion
			if (mvar_Files[i]==file)
			{
				//cerramos el fichero y si todo ha ido ok ponemos a null la posicion de la tabla donde estaba el puntero y restamos el numero de ficheros abiertos
				if (fclose(mvar_Files[i]) == 0)
				{
					mvar_Files[i]=NULL;
					OPENEDFILES--;

					return true;
				}
				else
					return false;
			}
		}
		return false;
	}
	else
		return false;
}

//***** lee de "file" numero de caracteres indicado como parametro en "numChars" almacenandolo en el parametro "Buffer" y devuelve los caracteres leidos
int ReadFile(FILE * file, char *buffer, int numChars)
{
	char c;
	int leidos=0;

	//leemos los caracters indicados por el usuario
	for (int i=0;i<numChars;i++)
	{
		//leemos el caracter haciendo casting de int a char
		c=(char)getc(file);

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

	return leidos;
}

//****** Escribe en un fichero los caracteres pasados en "Buffer" y devuelve el numero de caracteres escritos
int WriteFile(FILE *file, const char *buffer)
{
	char c=1;
	int carsEscritos=0;

	//escribimos los caracteres pasados en buffer hasta que se acabe la cadena o haya algun error al escribir en el fichero
	while (c != '\0' && c != EOF)
	{
		//cogemos el caracter a donde apunta el puntero
		c=*buffer;

		//guardamos en el fichero
		fputc((int)c,file);
		carsEscritos++;

		//pasamos a la siguiente posicion en memoria
		buffer++;
	}
	return 0;
}

//******* devuelve el numero de apariciones de una cadena en un fichero
int StringInFile(const char *string, FILE *file)
{
	int apariciones=0;
	int lngCadena=0;
	char *textoFichero=new (char);
	const char *posicionCadena=NULL;

	//aqui texto fichero apunta al inicio del texto del fichero
	ReadAllFile(file,textoFichero);	

	lngCadena=longuitudCadena(string);

	do 	
	{	//ahora texto fichero apunta a la posicion de la primera aparicion de la cadena asi que seguimos buscando a partir de ahi
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

//***** mete el un puntero a char pasado como parametro el contenido del fichero
void ReadAllFile(FILE *file, char *texto)
{
	char c=1;

	//colocamos el cursor al principio del fichero
	rewind(file);

	//leemos todos los caracteres del fichero y los guardamos en memoria
	while (c != EOF)
	{
		c=(char)getc(file);
		*texto=c;
		texto++;
	}

	*texto='\0';
}

//*******Devuelve un entero con la longuitud de una cadena
int longuitudCadena(const char *cadena)
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
