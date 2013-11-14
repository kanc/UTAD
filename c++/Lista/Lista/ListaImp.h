#include "stdafx.h"

struct ElementoLista {
	char *contenido;
	ElementoLista *siguiente;
};

class ListaImp {
	private:
		ElementoLista *mvar_pInicio;
		ElementoLista *mvar_pFin;
		ElementoLista *mvar_pActual;
		unsigned int mvar_iNumElementos;		

	public:	
		ListaImp();
		unsigned int Size();
		unsigned int Push(const char *psz);
		const char *First();
		const char *Next();
		const char *Pop();
		void Reset(); 
		void goFirst();
};
