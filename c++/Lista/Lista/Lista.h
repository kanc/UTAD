#include "stdafx.h"

struct Lista{	

	private:
		void *mvar_Impl;
	public:
		Lista();	
		unsigned int Size();
		unsigned int Push(const char *psz);
		const char *First();
		const char *Next();
		const char *Pop();
		void Reset();
		void goFirst();		
};

