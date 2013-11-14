#include "StdAfx.h"
#include "MyFileAccess.h"
#include "MyFileAccessImp.h"

#define Implementation ((MyFileAccessImp *)mvarAccess) 

MyFileAccess::MyFileAccess(void)
{
	mvarAccess=(MyFileAccessImp *)new MyFileAccessImp;
}

MyFileAccess::~MyFileAccess(void)
{
	delete (mvarAccess);
}

bool MyFileAccess::OpenFile(const char *filename, openMode mode)
{
	return Implementation->OpenFile(filename,(int) mode);	
}

bool MyFileAccess::CloseFile()
{
	return Implementation->CloseFile();
}

int MyFileAccess::ReadFile(char *buffer, int numChars, bool inicioFichero)
{
	return Implementation->ReadFile(buffer,numChars,inicioFichero);
}

int MyFileAccess::WriteFile(const char *buffer)
{
	return Implementation->WriteFile(buffer);
}

int MyFileAccess::StringInFile(const char *string)
{
	return Implementation->StringInFile(string);
}