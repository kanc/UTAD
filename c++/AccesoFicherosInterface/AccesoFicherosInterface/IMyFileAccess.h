namespace IMyFileAccess {

	struct fileType
	{
		unsigned int idFile;
		const char *filename;
		fileType();
		~fileType();
	};

	enum openMode
	{ READ=0, WRITE=1, READWRITE=2};

	fileType * OpenFile(const char *filename, openMode mode);
	bool CloseFile(fileType *file);
	unsigned int ReadFile(fileType *file, char *buffer, unsigned int numChars);
	unsigned int WriteFile(fileType *file, const char *buffer);
	unsigned StringInFile(const char *search, fileType *file);
}