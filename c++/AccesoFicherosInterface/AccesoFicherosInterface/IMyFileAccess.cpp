#include "stdafx.h"
#include "IMyFileAccess.h"
#include "NSmyFileAccess.h"

	IMyFileAccess::fileType * IMyFileAccess::OpenFile(const char *filename, openMode mode)
	{	
		fileType *fichero=new(fileType);
		unsigned int id;

		id=MyFileAccess::OpenFile(filename,mode);

		if (id!=0)
		{
			fichero->idFile= id;
			fichero->filename=filename;
			return fichero;
		}
		else
			return NULL;		
	}

	bool IMyFileAccess::CloseFile(fileType *file)
	{
		bool res=false;
		res=MyFileAccess::CloseFile(file->idFile);

		delete(file);

		return res;
	}

	unsigned int IMyFileAccess::ReadFile(fileType *file, char *buffer, unsigned int numChars)
	{
		return MyFileAccess::ReadFile(file->idFile,buffer,numChars);
	}

	unsigned int IMyFileAccess::WriteFile(fileType *file, const char *buffer)
	{
		return MyFileAccess::WriteFile(file->idFile,buffer);
	}

	unsigned int IMyFileAccess::StringInFile(const char *search, fileType *file)
	{
		return MyFileAccess::StringInFile(search,file->idFile);
	}