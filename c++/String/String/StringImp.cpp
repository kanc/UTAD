#include "stdafx.h"
#include "StringImp.h"
#include "String.h"
#include <string.h>
#include <stdlib.h>

StringImp::StringImp(const char* str)
{
	//indicamos en nuestra varible miembro la longuitud de la cadena
	mvar_iLength=strlen(str);

	//pedimos memoria para la cadena
	mvar_pszString=new char[mvar_iLength+1];
	
	//copiamos el contenido
	strcpy_s(mvar_pszString,mvar_iLength+1,str);

	//inicilizamos el buffer
	mvar_pszBuffer=NULL;
	mvar_iBufferLength=0;
	
}

StringImp::~StringImp()
{
	delete[] mvar_pszString;
	delete[] mvar_pszBuffer;
}


bool StringImp::EqualOperator(StringImp *op1, StringImp *op2) const
{
	if (!strcmp(op1->mvar_pszString,op2->mvar_pszString))
		return true;
	else
		return false;
}

bool StringImp::MinorOperator(StringImp *op1, StringImp *op2) const
{
	int res=strcmp(op1->mvar_pszString,op2->mvar_pszString);
	
	if (res < 0)
		return true;
	else
		return false;
}

bool StringImp::MayorOperator(StringImp *op1, StringImp *op2) const
{
	int res=strcmp(op1->mvar_pszString,op2->mvar_pszString);
	
	if (res > 0)
		return true;
	else
		return false;
}

char * StringImp::PlusOperator(StringImp *op1, StringImp *op2) const
{	
	//gestionamos la memoria del buffer para almacenar la longuitd de las dos cadenas
	ManageBufferMem(op1->mvar_iLength + op2->mvar_iLength);

	//copiamos la primera cadena al buffer
	strcpy(mvar_pszBuffer,op1->mvar_pszString);

	//añadimos la segunda
	strcat(mvar_pszBuffer,op2->mvar_pszString);

	return mvar_pszBuffer;

}

char * StringImp::PlusOperator(StringImp *op1,char c) const
{	
	//gestionamos la memoria del buffer para almacenar la longuitd de las dos cadenas
	ManageBufferMem(op1->mvar_iLength +1);

	//copiamos la primera cadena al buffer
	strcpy(mvar_pszBuffer,op1->mvar_pszString);

	//añadimos la segunda
	strcat(mvar_pszBuffer,&c);

	return mvar_pszBuffer;

}

void StringImp::IncrementOperator(StringImp *op2)
{
	//gestionamos la memoria del buffer para almacenar la cadena actual
	ManageBufferMem(mvar_iLength);

	//copiamos la cadena actual al buffer
	strcpy(mvar_pszBuffer,mvar_pszString);

	//gestionamos la memoria pero en vez del buffer, de nuestro puntero a la cadena de la instancia para guardar las dos cadenas
	ManageStringMem(mvar_iLength + op2->mvar_iLength);

	//copiamos del buffer a la cadena principal
	strcpy(mvar_pszString,mvar_pszBuffer);
	
	//concatenamos la cadena pasada a la propia cadena de la clase
	strcat(mvar_pszString,op2->mvar_pszString);

}

void StringImp::IncrementOperator(char c)
{
	//gestionamos la memoria del buffer para almacenar la cadena actual
	ManageBufferMem(mvar_iLength);

	//copiamos la cadena actual al buffer
	strcpy(mvar_pszBuffer,mvar_pszString);

	//gestionamos la memoria pero en vez del buffer, de nuestro puntero a la cadena de la instancia para cadena + caracter 
	ManageStringMem(mvar_iLength+1);

	//copiamos del buffer a la cadena principal
	strcpy(mvar_pszString,mvar_pszBuffer);
	
	//concatenamos el caracter a a la propia cadena de la clase
	strcat(mvar_pszString,&c);

}

void StringImp::CopyOperator(StringImp *op2)
{
	//gestionamos la memoria de nuestra cadena
	ManageStringMem(op2->mvar_iLength);

	//copiamos el contenido de la cadena del operador 2
	strcpy(mvar_pszString,op2->mvar_pszString);
}

void StringImp::CopyOperator(char c)
{
	//gestionamos la memoria de nuestra cadena
	ManageStringMem(1);
	
	*mvar_pszString=c;
	mvar_pszString++;
	*mvar_pszString='\0';
	mvar_pszString--;

}

char * StringImp::Mid(unsigned int ofs, unsigned int n) const
{
	unsigned int limite;	

	//damos la memmoria necesaria al buffer
	ManageBufferMem(n);

	//calculamos hasta que posicion se requiere
	limite=ofs+n;	

	//si nos pasamos, el limite es el tamaño de la cadena
	if (limite > mvar_iLength)
		limite=mvar_iLength;		
	
	//cogemos el numero de caracteres solicitados
	for (int unsigned i=ofs; i< limite;i++)
	{
		//asignamos el contenido de la posicion i de la cadena al buffer
		*mvar_pszBuffer=mvar_pszString[i];
		//avanzamos a la siguiente posicion de memoria
		mvar_pszBuffer++;
	}
	
	//señalamos el fin de cadena
	*mvar_pszBuffer='\0';

	//retrocedemos el puntero para que apunte al inicio de la cadena
	for (int unsigned i=ofs; i<limite;i++)			
		mvar_pszBuffer--;	

	return mvar_pszBuffer;
}

char * StringImp::Right(unsigned int n) const
{	
	//si se piden mas caracteres de los que tiene la cadena cogemos solo los
	if (n > mvar_iLength)
		n=mvar_iLength;
	
	ManageBufferMem(n);

	for (unsigned int i=mvar_iLength-n; i<mvar_iLength-1;i++)
	{
		*mvar_pszBuffer=mvar_pszString[i];
		mvar_pszBuffer++;
	}
	
	*mvar_pszBuffer='\0';

	for (int unsigned i=mvar_iLength-n; i<mvar_iLength-1;i++)
	{		
		mvar_pszBuffer--;
	}
	
	return mvar_pszBuffer;	
}

void StringImp::FromInt(int val, char *buffer)
{	
	_itoa_s(val,buffer,10,10);
}

void StringImp::HexFromInt(int val,char *buffer)
{
	_itoa_s(val,buffer,strlen(buffer)+1,16);
}

void StringImp::FromFloat(float val,char *buffer)
{
	sprintf_s(buffer,strlen(buffer),"%f",val);		
}

int StringImp::ToInt() const
{	
	return atoi(mvar_pszString);
}

float StringImp::ToFloat() const
{
	return atof(mvar_pszString);
}

char* StringImp::ToCString() const
{
	return mvar_pszString;
}

int StringImp::Length() const
{
	//no incluye en caracter de fin de cadena
	return mvar_iLength;
}

unsigned int StringImp::totalFinds(const StringImp* find) const
{
	const char *pszTemp;
	unsigned finds=0;
	unsigned int findlength;

	pszTemp=strstr(mvar_pszString,find->mvar_pszString);
	findlength=strlen(find->mvar_pszString);

	while (pszTemp != NULL)
	{
		finds++;
		pszTemp+=findlength; //para que no vuelva a encontrarlo siempre en el mismo sitio
		pszTemp=strstr(pszTemp,find->mvar_pszString);
	}

	return finds;
}

char * StringImp::Replace(const StringImp* find, const StringImp* rep) const
{
	unsigned int findLength;
	unsigned int repLength;
	unsigned int totalfinds;
	const char *pszTemp;
	char *pInicial;
	unsigned int posMainString=0;

	findLength=strlen(find->mvar_pszString);
	repLength=strlen(rep->mvar_pszString);

	//creo que es mas optimo buscar la primera vez cuantas veces aperece la cadena a buscar y dar memoria en consecuencia que andar redimensionando el buffer
	//cada vez que encuentra una, ya que eso conlleva otra operacion de copiar el contenido a otro buffer temporal y luego de nuevo al buffer principal
	totalfinds=totalFinds(find);

	//comprobamos si necesitaremos mas memoria de la que tiene la cadena para el buffer
	if (repLength > findLength)
		ManageBufferMem(mvar_iLength + ((repLength - findLength) * totalfinds));
	else //o si necesitamos menos
		ManageBufferMem(mvar_iLength - ((findLength-repLength) * totalfinds));

	//una vez tenemos el buffer inicializado y apuntando a la primera posicion de memoria, guardamos esa posicion para volver a ella
	pInicial=mvar_pszBuffer;
	
	//buscamos la cadena
	pszTemp=strstr(mvar_pszString,find->mvar_pszString);

	//si la encuentra
	while (pszTemp != NULL)
	{
		//recorremos nuestra cadena copiando los caracteres hasta que nos encontremos en la posicion donde se encuentra la cadena a reemplazar
		for (unsigned int i=posMainString; i < mvar_iLength; i++)
		{
			if (&mvar_pszString[i]!=pszTemp)
			{	*mvar_pszBuffer=mvar_pszString[i];
				*mvar_pszBuffer++;
				posMainString++; //vamos registrando cuantas posiciones nos vamos moviendo
			}
			else				
				break;		
		}

		//ya tenemos copiado hasta donde encuentra la cadena, ahora añadimos la nueva cadena
		strcpy(mvar_pszBuffer,rep->mvar_pszString);

		//avanzamos el puntero las posicion de la nueva cadena para seguir metiendo datos
		mvar_pszBuffer+=repLength;
		posMainString+=findLength; //desde donde seguira buscando en nuestra cadena principal
		pszTemp+=findLength; //para que no vuelva a encontrar otra la misma concurrencia

		//buscamos la siguiente concurrencia pero esta vez en el puntero devuelto anteriormente
		pszTemp=strstr(pszTemp,find->mvar_pszString);

	}	

	//ahora seguimos copiando el contenido de la ultima concurrencia hasta el final de la cadena
	for (unsigned int i=posMainString; i < mvar_iLength; i++)
	{
		*mvar_pszBuffer=mvar_pszString[i];
		mvar_pszBuffer++;
	}

	//metemos el fin de cadena
	*mvar_pszBuffer='\0';

	//apuntamos a la posicion inicial de la cadena
	mvar_pszBuffer=pInicial;

	return mvar_pszBuffer;

}

int StringImp::Find(const StringImp *toFind, unsigned int ofs) const
{	
	char *pszTemp;
	unsigned int pos=0;
	
	//comprobamos que el offset sea menor que la longuitud de la cadena
	if (ofs<=mvar_iLength)
	{	ManageBufferMem(mvar_iLength);

		//copiamos la cadena principal al buffer
		strcpy(mvar_pszBuffer,mvar_pszString);

		//avanzamos la posicion del puntero para que empieze a buscar a partir del offset
		mvar_pszBuffer+=ofs;

		//obtenemos un puntero a la posicion del buffer donde esta la cadena buscada
		pszTemp=strstr(mvar_pszBuffer,toFind->mvar_pszString);

		//si ha encontrado la cadena
		if (pszTemp!=NULL)
			//recorremos desde el offset hasta el final de la cadena buscando la posicion de memoria que coincida con el puntero devuelto
			for (unsigned int i=0; i < mvar_iLength-ofs; i++)
				if (&mvar_pszBuffer[i]!=pszTemp)
					pos++;
				else				
					break;				
		else
			pos=-1; //no encuentra la cadena

		return pos+ofs; //devolvemos la posicion relativa al inicio de la cadena

	}
	else return -1;	
}

const char * StringImp::ToUpper() const
{	
	return ToUpperLower(TOUPPER);
}

const char * StringImp::ToLower() const
{	
	
	return ToUpperLower(TOLOWER);

}

const char * StringImp::ToUpperLower(EUpLowOperation operation) const
{
	//gestionamos la memoria para el buffer
	ManageBufferMem(mvar_iLength);

	//copiamos la cadena al buffer para manejarla	
	strcpy(mvar_pszBuffer,mvar_pszString);

	//recorremos la candena
	for (unsigned int i=0; i < mvar_iLength; i++)
	{
		//si queremos transformar a minusculoa
		if (operation==TOLOWER)
			if(mvar_pszBuffer[i]>='a' && mvar_pszBuffer[i]<='z')		
				mvar_pszBuffer[i]=mvar_pszBuffer[i]^0x20;
		
		else //transformar a mayuscula
			if(mvar_pszBuffer[i]>='A' && mvar_pszBuffer[i]<='Z')		
				mvar_pszBuffer[i]=mvar_pszBuffer[i]^0x20;

	}
		
	return mvar_pszBuffer;
}

char * StringImp::LTrim() const
{	
	unsigned int pos=0;
	char c;
	
	//cogemos el primera caracter de la cadena
	c=mvar_pszString[0];

	//mimentras solo encuentre espacios
	while (c==32)
	{	pos++;
		c=mvar_pszString[pos];
	}

	//damos memoria al buffer
	ManageBufferMem(mvar_iLength - pos);

	//vamos llenando el buffer con el contenido de la cadena a partir de la posicion obtenido
	for (unsigned int i=pos-1; i<mvar_iLength;i++)
	{
		*mvar_pszBuffer=mvar_pszString[i];
		mvar_pszBuffer++;
	}

	//colocamos el caracter de fin de cadena y volvemos al inicio
	*mvar_pszBuffer='\0';
	mvar_pszBuffer-=(mvar_iLength - pos);

	return mvar_pszBuffer;

}

char * StringImp::RTrim() const
{
	unsigned int pos=mvar_iLength-1;
	char c;
	
	//cogemos el ultimo caracter de la cadena
	c=mvar_pszString[pos];

	while (c==32) 
	{
		pos--;
		c=mvar_pszString[pos];
	}

	ManageBufferMem(pos+1);

	for (unsigned int i=0; i <= pos; i++)
	{
		*mvar_pszBuffer=mvar_pszString[i];
		mvar_pszBuffer++;
	}

	//colocamos el caracter de fin de cadena y volvemos al inicio
	*mvar_pszBuffer='\0';
	mvar_pszBuffer-= pos;

	return mvar_pszBuffer;
}

char * StringImp::Trim() const
{
	unsigned int chars=0;
	
	//estamos dando mas memoria de la necesaria, pero otra opcion seria guardarlo en un buffer local para una vez saber los caracteres, pedir la memoria justa para el buffer y copiar el contenido de uno a otro
	//me parece menos costoso mi opcion.
	ManageBufferMem(mvar_iLength);

	//recorremos la cadena y escribimos en el buffer los caracteres que no sean espacios
	for (unsigned int i=0; i<mvar_iLength;i++)
	{
		if (mvar_pszString[i]!=32)
		{
			*mvar_pszBuffer=mvar_pszString[i];
			mvar_pszBuffer++;
			chars++;
		}		
	}

	//ponemos el fin de cadena y volvemos a la posicion inicial
	*mvar_pszBuffer='\0';
	mvar_pszBuffer-=chars;

	return mvar_pszBuffer;
}

char * StringImp::LSet(unsigned int len, char c) const
{
	int total;

	//damos memoria al buffer
	if (len > mvar_iLength)
		ManageBufferMem(len);
	else
		ManageBufferMem(mvar_iLength);
	
	//calculamos los caracteres a rellenar
	total=len-mvar_iLength;

	//si es negativo es que la longuitud solicitada es menor que la que ya tiene la cadena
	if (total<0)
		total=0;

	for (int i=0; i < total; i++)
		mvar_pszBuffer[i]=c;	

	//colocamos el caracter fin de cadena y copiamos nuestra cadena principal
	mvar_pszBuffer[mvar_iBufferLength]='\0';
	strcat(mvar_pszBuffer,mvar_pszString);

	return mvar_pszBuffer;
	
}

char * StringImp::RSet(unsigned int len, char c) const
{
	if (len > mvar_iLength)
		ManageBufferMem(len);
	else
		ManageBufferMem(mvar_iLength);	

	mvar_pszBuffer[0]='\0';
	strcat(mvar_pszBuffer,mvar_pszString);

	for (unsigned int i=mvar_iLength; i < len ; i++)
		mvar_pszBuffer[i]=c;
	
	mvar_pszBuffer[mvar_iBufferLength]='\0';
	
	return mvar_pszBuffer;
	
}

char * StringImp::StripAfterChar(char c) const
{
	int i=mvar_iLength;

	ManageBufferMem(mvar_iLength);

	for (i; i >= 0; i--)
	{	if (mvar_pszString[i]==c)
			break;
	}

	if (i>0)
	{
		strncpy(mvar_pszBuffer,mvar_pszString,i);
		mvar_pszBuffer[i]='\0';
	}	
	else
		strcpy(mvar_pszBuffer,mvar_pszString);	

	return mvar_pszBuffer;

}

char * StringImp::StripBeforeChar(char c) const
{
	int i=mvar_iLength;

	ManageBufferMem(mvar_iLength);

	for (i; i >= 0; i--)
	{	if (mvar_pszString[i]==c)
			break;
	}

	if (i>0)
	{
		return Mid(i+1,mvar_iLength-i);
	}	
	else
	{	strcpy(mvar_pszBuffer,mvar_pszString);	
		return mvar_pszBuffer;
	}	

}

char * StringImp::StripExt() const
{
	return StripAfterChar('.');
}
char * StringImp::StripDir() const
{
	return StripBeforeChar('\\');
}
char * StringImp::ExtractExt() const
{
	return StripBeforeChar('.');
}
char * StringImp::ExtractDir() const
{
	return StripAfterChar('\\');
}

String StringImp::Read(const StringImp *filename)
{
	FILE *file;
	long nBytes;
	char *pszFile=NULL;
	unsigned int leidos=0;

	fopen_s(&file, filename->mvar_pszString,"r");

	if (file !=NULL)
	{	
		fseek(file, 0, SEEK_END); 
		nBytes = ftell(file);
		
		pszFile=new char[nBytes+1];		
		
		rewind(file);		
		leidos=fread(pszFile,sizeof(char),nBytes,file);
			
		if (!leidos)
			pszFile[0]='\0';
		else
			pszFile[leidos-1]='\0';
		
		fclose(file);		

		String newobj=String(pszFile);
		
		return newobj;
	}
	else
		return NULL;
}

void StringImp::Write(const StringImp* filename, bool append) const
{
	FILE *file;	

	if (append)
		fopen_s(&file, filename->mvar_pszString,"a");
	else
		fopen_s(&file, filename->mvar_pszString,"w");

	if (file !=NULL)
	{
		fwrite(mvar_pszString,sizeof(char),mvar_iLength,file);

		fclose(file);
	}
}

void StringImp::ManageBufferMem(unsigned int memSize) const
{	
	//si el buffer ha sido inicializado antes
	if (mvar_pszBuffer!=NULL)
	{		
		//si es menor que la memoria necesaria lo redimensionamos
		if (mvar_iBufferLength < memSize)
		{
			mvar_pszBuffer=NULL;
			delete[] mvar_pszBuffer;
			mvar_pszBuffer=new char[memSize+1];
		}
		else //si es suficiente ponemos el caracter fin de cadena en la primera posicion
			*mvar_pszBuffer='\0';
	}
	else //si no ha sido inicializado lo hacemos
		mvar_pszBuffer=new char[memSize+1];

	mvar_iBufferLength=memSize;
}

void StringImp::ManageStringMem(unsigned int memSize)
{
	//si la cadena ha sido inicializado antes
	if (mvar_pszString!=NULL)
	{		
		//si el tamaño actual es menor que la memoria necesaria lo redimensionamos
		if (mvar_iLength < memSize)
		{
			mvar_pszString=NULL;
			delete[] mvar_pszString;
			mvar_pszString=new char[memSize+1];	//damos un byte mas para el fin de cadena		
		}
		else //si es suficiente ponemos el caracter fin de cadena en la primera posicion
			*mvar_pszString='\0';
	}
	else //si no ha sido inicializado lo hacemos
		mvar_pszString=new char[memSize+1];

	//actualizamos el tamaño de la cadena
	mvar_iLength=memSize;

}