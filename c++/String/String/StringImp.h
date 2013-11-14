class String;

class StringImp
{	
	private:			
		enum EUpLowOperation
		{ TOUPPER, TOLOWER};

		char *mvar_pszString;		
		mutable unsigned int mvar_iLength;
		mutable int unsigned mvar_iBufferLength;
		mutable char *mvar_pszBuffer;

		void ManageBufferMem(unsigned int memSize) const; 
		void ManageStringMem(unsigned int memSize);
		unsigned int totalFinds(const StringImp* find) const;
		char * StripAfterChar(char c) const;
		char * StripBeforeChar(char c) const;
		

	public:		
		StringImp(const char* str = "");				
		~StringImp();		

		int Length() const;		

		bool EqualOperator(StringImp *op1, StringImp *op2) const;
		bool MinorOperator(StringImp *op1, StringImp *op2) const;
		bool MayorOperator(StringImp *op1, StringImp *op2) const;
		char* PlusOperator(StringImp *op1, StringImp *op2) const;
		char* PlusOperator(StringImp *op1, char c) const;
		void CopyOperator(StringImp *op2);
		void CopyOperator(char c);
		void IncrementOperator(StringImp *op2);
		void IncrementOperator(char c);		

		static void FromInt(int val, char *buffer) ;
		static void HexFromInt(int val,char *buffer) ;
		static void FromFloat(float val, char *buffer) ;

		int ToInt() const; 
		float ToFloat() const;
		char * ToCString() const;		
		char * Mid(unsigned int ofs, unsigned int n) const;
		char * Right(unsigned int n) const;
		int Find(const StringImp *str, unsigned int ofs) const;
		char * Replace(const StringImp* find, const StringImp* rep) const;
		const char * ToUpperLower(EUpLowOperation operation) const;
		const char * ToUpper() const;
		const char * ToLower() const;

		char * LTrim() const;
		char * RTrim() const;
		char * Trim() const;
		char * LSet(unsigned int len, char c) const; //hasta que la cadena alcance la longuitud "len" poner con el caracter c por la izquierda
		char * RSet(unsigned int len, char c) const;

		char * StripExt() const; //quitar extension de una cadena tipo nombre fichero
		char * StripDir() const; 
		char * ExtractExt() const; //devuelve la extension de una cadena de tipo nombre de fichero
		char * ExtractDir() const;
   
		static String Read(const StringImp* filename); //devuelve el contenido de un fichero en una cadena
		void Write(const StringImp* filename, bool append = true) const; //escribe el contenido de una candena, sobreescribiendo o añadiendo


};