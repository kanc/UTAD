// AccesoFicherosClases.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyFileAccess.h"

int _tmain(int argc, _TCHAR* argv[])
{
	MyFileAccess *file=new MyFileAccess();
	MyFileAccess *file2=new MyFileAccess();
	char *texto=new char[100];
	char *texto2=new char[100];

	file->OpenFile("test.txt",MyFileAccess::READ);
	file->ReadFile(texto,10);

	file2->OpenFile("test2.txt",MyFileAccess::READWRITE);
	file2->WriteFile("PROBANDO PROBANDO");
	file2->ReadFile(texto2,10);

	printf("%s, %s",texto,texto2);
	getchar();
	
	file->CloseFile();
	file2->CloseFile();

	delete file;
	delete file2;
	delete[] texto;
	delete[] texto2;

	return 0;
}

