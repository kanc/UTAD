#include "stdafx.h"
#include "ListaImp.h"
#include <string.h>

ListaImp::ListaImp()
{
	mvar_pInicio=NULL;
	mvar_pFin=NULL;
	mvar_pActual=NULL;
	mvar_iNumElementos=0;
}

unsigned int ListaImp::Size()
{
	return mvar_iNumElementos;
}

unsigned int ListaImp::Push(const char *psz)
{
	ElementoLista *newElement=new ElementoLista();

	//damos memoria y copiamos el contenido de la cadena en el elemento
	newElement->contenido=new char[strlen(psz)+1];
	strcpy_s(newElement->contenido,strlen(psz)+1,psz);

	newElement->siguiente=NULL;

	if (mvar_iNumElementos==0)
	{
		//el inicio, fin y actual de la lista apuntan al nuevo elemento
		mvar_pInicio=newElement;
		mvar_pFin=newElement;		
		mvar_pActual=newElement;
	}
	else
	{
		//le decimos al ultimo elemento que el siguiente es el recien creado
		mvar_pFin->siguiente=newElement;
		
		//el fin de la lista apunta el nuevo elemento
		mvar_pFin=newElement;
	}

	//incrementamos el numero de elementos
	mvar_iNumElementos++;
	
	return mvar_iNumElementos;
}

const char * ListaImp::First()
{
	if (mvar_pInicio != NULL)
	{
		return mvar_pInicio->contenido;
	}
	else
		return NULL;
}

const char * ListaImp::Next()
{
	if (mvar_pActual!=NULL)
	{
		const char *temp=mvar_pActual->contenido;
		mvar_pActual=mvar_pActual->siguiente;

		return temp;
	}
	else
		return NULL;
}

const char * ListaImp::Pop()
{		
	//apuntamos el contenido del primer elemento
	ElementoLista *pElem=mvar_pInicio;

	if (pElem!=NULL)
	{	//aqui estamos teniendo un memory leak seguramente porque estoy haciendo un new sin delete
		//pero no puedo devolver el contenido del elemento porque lo tengo que borrar primero...
		char *temp=new char[strlen(pElem->contenido)+1];
		strcpy(temp,pElem->contenido);

		//movemos el primero elemento al siguiente
		mvar_pInicio=mvar_pInicio->siguiente;

		strcpy(temp,pElem->contenido);

		//borramos el elemento
		delete pElem;

		//decrementamos el numero
		mvar_iNumElementos--;

		return temp;
	}
	else
		return NULL;
}

void ListaImp::goFirst()
{
	mvar_pActual=mvar_pInicio;
}

void ListaImp::Reset()
{
	while (mvar_iNumElementos>0)	
		Pop();
	
	mvar_pActual=NULL;
	mvar_pInicio=NULL;
	mvar_pFin=NULL;
}

