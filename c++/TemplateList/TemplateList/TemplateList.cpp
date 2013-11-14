// TemplateList.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "array.h"
#include "list.h"

bool isMinor(int &op1, int &op2);

bool isMinor(int &op1, int &op2){
	if (op1 < op2)
		return true;
	else
		return false;
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*Array <char> miArray(2);	

	miArray.Add('a');
	miArray.Add('b');
	miArray.Add('c');

	printf("%c %c %c %c %c\n", miArray[0], miArray[1], miArray[2], miArray[3], miArray[4]);

	//miArray.Clear();	

	miArray.Add('b');
	miArray.Add('d');
	miArray.Add('e');
	miArray.Add('b');

	printf("%c %c %c %c %c\n", miArray[0], miArray[1], miArray[2], miArray[3], miArray[4]);

	miArray.RemoveEach('b');

	miArray.RemoveLast();

	//miArray.RemoveAt(2);

	printf("%c %c %c %c %c\n", miArray.Last(), miArray[1], miArray[2], miArray[3], miArray[4]);

	miArray.Clear();
	getchar(); */

	List <int> *miLista=new List <int>;	

	miLista->Add(15);
	miLista->Add(5);
	
	List <int>::Node *nodo=miLista->Last();

	miLista->InsertAfter(nodo,13);

	miLista->Add(22);
	miLista->Add(2);

	Array<int> miArray=miLista->ToArray();	

	printf("La lista pasada a Array\n");
	for (int i=0; i < miArray.Size();i++)
	{
		printf("%i: ", miArray[i]);
	}

	miLista->Sort(&isMinor);	

	//miLista->Clear();

	printf("\nLa lista ordenada\n");

	while (!miLista->IsEmpty())
	{
		nodo=miLista->Last();
		printf("%i: ", nodo->Value());
		miLista->Remove(nodo);
	}

	//printf("%i", nodo->Value());
	getchar();
		
	delete miLista;	

	return 0;
}

