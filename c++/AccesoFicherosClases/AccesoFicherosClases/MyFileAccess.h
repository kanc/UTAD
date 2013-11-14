class MyFileAccess
{
	private:
		void *mvarAccess;
	public:
		enum openMode
		{
			READ=0,WRITE=1,READWRITE=2	
		};

		MyFileAccess(void);
		~MyFileAccess(void);

		bool OpenFile(const char *filename, openMode mode);
		bool CloseFile();
		int ReadFile(char *buffer, int numChars, bool inicioFichero=true);
		int WriteFile(const char *buffer);
		int StringInFile(const char *string);		
};

