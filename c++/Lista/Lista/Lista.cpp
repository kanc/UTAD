#include "stdafx.h"
#include "Lista.h"
#include "ListaImp.h"

#define Impl ((ListaImp *)mvar_Impl)

Lista::Lista() 
{
	mvar_Impl=(ListaImp *)new ListaImp;
}

unsigned int Lista::Push(const char *psz)
{
	if (psz!=NULL)
		return Impl->Push(psz);
	else
		return 0;
		
}

unsigned int Lista::Size()
{
	return Impl->Size();
}

const char * Lista::Next()
{
	return Impl->Next();
}

void Lista::goFirst()
{
	Impl->goFirst();
}

const char * Lista::Pop()
{
	return Impl->Pop();
}

void Lista::Reset()
{
	Impl->Reset();
}