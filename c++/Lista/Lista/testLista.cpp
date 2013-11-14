// Lista.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Lista.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Lista *milista=new Lista();

	milista->Push("uno");
	milista->Push("dos");
	milista->Push("tres");	

	for (unsigned int i=0;i < milista->Size();i++)	
		printf("%s\n",milista->Next());
	
	
	printf("borrando...\n");

	milista->Reset();
	
	printf("no. elementos: %i\n",milista->Size());
	
	getchar();

	milista->Push("otro");
	milista->Push("otro mas");
	milista->Push("otro pa la saca");

	for (unsigned int i=0;i < milista->Size();i++)	
		printf("%s\n",milista->Next());
	
	getchar();

	delete milista;

	return 0;
}

