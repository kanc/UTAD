
class String {

	private:
		void *mvar_ImpAcc;
		
	public:
		String(const char* str = "");
		String(const String& str);
		~String();		

		bool operator==(const String& other) const; //hecho
		bool operator!=(const String& other) const; //hecho
		bool operator<(const String& other) const; //si el primer operando es menor alfabeticamente hablando
		bool operator>(const String& other) const; //hecho
		String operator+(const String& other) const; //hecho
		String operator+(char c) const; //hecho
		String& operator=(const String& other); //hecho
		String& operator=(char c); //???
		String& operator+=(const String& other); //hecho
		String& operator+=(char c); //hecho
		char& operator[](unsigned int pos); //hecho para acceder usando un indice
		const char& operator[](unsigned int pos) const; //??

		int Length() const; //hecho		

		static String FromInt(int val); // hecho -nos devuelve la cadena con el entero (itoa...
		static String HexFromInt(int val); //hecho
		static String FromFloat(float val); //hecho

		int ToInt() const; //hecho
		float ToFloat() const; //hecho
		const char* ToCString() const; //hecho

		String Left(unsigned int n) const; //hecho
		String Right(unsigned int n) const;
		String Mid(unsigned int ofs, unsigned int n) const; //hecho devuelve n caracteres a partir de la posicion ofs
		String Replace(const String& find, const String& rep) const; //hecho
		int Find(const String& str, int ofs) const; //hecho

		String ToUpper() const; //hecho
		String ToLower() const; //hecho
		String LTrim() const; //hecho
		String RTrim() const; //hecho
		String Trim() const; //hecho
		String LSet(unsigned int len, char c) const; //hecho
		String RSet(unsigned int len, char c) const; //hecho

		String StripExt() const; //hecho
		String StripDir() const; //hecho
		String ExtractExt() const; //hecho
		String ExtractDir() const; //hecho
   
		static String Read(const String& filename); //hecho devuelve el contenido de un fichero en una cadena
		void Write(const String& filename, bool append = true) const; //escribe el contenido de una candena, sobreescribiendo o añadiendo
};