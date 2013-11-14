// ClasesVirtuales.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

class CBase
{
public:
	CBase()
	{
		printf("CBase()\n");
		m_iValueBase = 0;
		MetodoV1();
	}

	virtual ~CBase()
	{
		printf("~CBase()\n");
	}

	virtual int MetodoV1()
	{
		printf("CBase::MetodoV1()\n");
		return 0;
	}

	virtual int MetodoV2()
	{
		printf("CBase::MetodoV2()\n");
		return 0;
	}

	int Metodo2()
	{
		MetodoV1();
		return 0;
	}

private:
	int m_iValueBase;
};

// ***********************************************************
class CDerived : public CBase
{
	public:
	CDerived()
	{
		printf("CDerived()\n");
		m_iValueDerived = 0;
	}

	~CDerived()
	{
		printf("~CDerived()\n");
	}

	virtual int MetodoV1()
	{
		printf("CDerived::MetodoV1()\n");
		return 0;
	}

	virtual int MetodoV2()
	{
		printf("CDerived::MetodoV2()\n");
		return 0;
	}

private:
	int m_iValueDerived;
};

// ***********************************************************
class CDerived2 : public CBase
{
	public:
	CDerived2()
	{
		printf("CDerived2()\n");
		m_iValueDerived = 0;
	}

	~CDerived2()
	{
		printf("~CDerived2()\n");
	}

	virtual int MetodoV1()
	{
		printf("CDerived::MetodoV1_2()\n");
		return 0;
	}

	virtual int MetodoV2()
	{
		printf("CDerived::MetodoV2_2()\n");
		return 0;
	}

private:
	int m_iValueDerived;
};

// ***********************************************************
int _tmain(int argc, _TCHAR* argv[])
{
	CBase *pBase = new CDerived();
	CBase *pBase2 = new CDerived();

	// Llamada a métodos virtuales
	pBase->Metodo2();
	pBase->MetodoV1();
	pBase->CBase::MetodoV1();

	// Tamaño de las clases
	int iSize = sizeof(CDerived);

	// RTTI
	{
		pBase = new CDerived;
		int iSizeBase = sizeof(CBase);
		int iSizeDerived = sizeof(CDerived);
		CDerived *pDerived		= dynamic_cast<CDerived *>(pBase);
		CDerived2 *pDerived2	= dynamic_cast<CDerived2 *>(pBase);
		pDerived->MetodoV1();
	}


	// Borrado desde la clase base. Destructores virtuales
	delete pBase;

	getchar();

	return 0;
}

