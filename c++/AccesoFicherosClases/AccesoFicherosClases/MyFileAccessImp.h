#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class MyFileAccessImp
{
	private:
		FILE *mvar_File;

		void ReadAllFile(char *texto);
		unsigned int StringLength(const char *cadena) const;				
		void CastOpenMode(unsigned int mode, char * type) const;
		
	public:
		MyFileAccessImp();
		~MyFileAccessImp();
		bool OpenFile(const char *filename, int mode);
		bool CloseFile();
		unsigned int ReadFile(char *buffer, unsigned int numChars,bool inicioFichero=true);
		unsigned int WriteFile(const char *buffer);
		unsigned int StringInFile(const char *string);

};
