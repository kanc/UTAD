#include "stdafx.h"
#include "String.h"
#include "StringImp.h"

#define Impl ((StringImp *)mvar_ImpAcc)  

//****** Constructores ***********
String::String(const char* str)
{
	mvar_ImpAcc=(StringImp *)new StringImp(str);				
}

String::String(const String& str)
{
	if (&str!=NULL)
		mvar_ImpAcc=(StringImp *)new StringImp(str.ToCString());
	else
		mvar_ImpAcc=(StringImp *)new StringImp("");
}

String::~String()
{
	delete mvar_ImpAcc;
}

//****** Operadores ***********
bool String::operator!=(const String& other) const
{
	if (&other !=NULL)
		return !Impl->EqualOperator((StringImp *)mvar_ImpAcc,(StringImp *)other.mvar_ImpAcc);
	else
		return false;
}

bool String::operator==(const String& other) const
{
	if (&other !=NULL) 
		return Impl->EqualOperator((StringImp *)mvar_ImpAcc,(StringImp *)other.mvar_ImpAcc);
	else
		return false;
}

bool String::operator<(const String& other) const
{
	if (&other !=NULL)
		return Impl->MinorOperator((StringImp *)mvar_ImpAcc,(StringImp *)other.mvar_ImpAcc);
	else
		return false;
	
}

bool String::operator>(const String& other) const
{
	if (&other!=NULL)
		return Impl->MayorOperator((StringImp *)mvar_ImpAcc,(StringImp *)other.mvar_ImpAcc);
	else
		return false;
	
}
String String::operator+(const String& other) const
{
	String newobj;

	if (&other !=NULL)
		 newobj=String(Impl->PlusOperator((StringImp *)mvar_ImpAcc,(StringImp *)other.mvar_ImpAcc));
	else
		 newobj=String(*this);

	return newobj;
}

String String::operator+(char c) const
{
	String newobj=String(Impl->PlusOperator((StringImp *)mvar_ImpAcc,c));

	return newobj;
}

String& String::operator=(const String& other)
{
	//aqui no tengo muy claro que funcionalidad queremos en caso de que el segundo operando no este instanciado, en principio no hacemos nada.
	if (&other !=NULL)	
		Impl->CopyOperator((StringImp *)other.mvar_ImpAcc);
		
	return *this;
}

String& String::operator=(char c)
{
	Impl->CopyOperator(c);
	return *this;
}

String& String::operator+=(const String& other)
{
	if (&other !=NULL)
		Impl->IncrementOperator((StringImp *)other.mvar_ImpAcc);

	return *this;
}

String& String::operator+=(char c)
{
	Impl->IncrementOperator(c);

	return *this;
}

char& String::operator[](unsigned int pos)
{
	return *(Impl->Mid(pos,1));
}

//****** Funciones ***********
String String::FromInt(int val)
{
	char *pszText=new char[10];

	StringImp::FromInt(val,pszText);

	String newobj(pszText);

	delete[] pszText;
	
	return newobj;

}

String String::HexFromInt(int val)
{
	char *pszText=new char[10];

	StringImp::HexFromInt(val,pszText);

	String newobj=String(pszText);

	delete[] pszText;
	
	return newobj;

}

String String::FromFloat(float val)
{
	char *pszText=new char[10];

	StringImp::FromFloat(val,pszText);

	String newobj= String(pszText);

	pszText = NULL;
	delete[] pszText;
	
	return newobj;
}

int String::ToInt() const
{
	return Impl->ToInt();
}

float String::ToFloat() const
{
	return Impl->ToFloat();
}

const char* String::ToCString() const
{
	return Impl->ToCString();
}

String String::Left(unsigned int n) const
{	
	String obj= String(Impl->Mid(0,n));

	return obj;
}

String String::Right(unsigned int n) const
{	
	String obj= String(Impl->Right(n));

	return obj;
}

String String::Mid(unsigned int ofs, unsigned int n) const
{	
	String obj= String(Impl->Mid(ofs,n));

	return obj;
}

int String::Length() const
{
	return Impl->Length();
}

int String::Find(const String& str, int ofs) const
{
	if (&str !=NULL)
		return Impl->Find((StringImp *)str.mvar_ImpAcc,ofs);
	else
		return 0;
}

String String::Replace(const String& find, const String& rep) const
{
	if (&find!=NULL && &rep!=NULL)
	{
		String newObj=String(Impl->Replace((StringImp *)find.mvar_ImpAcc,(StringImp *)rep.mvar_ImpAcc));

		return newObj;
	}
	else
		return NULL;
}

String String::ToUpper() const
{
	String newObj=String(Impl->ToUpper());

	return newObj;
}

String String::ToLower() const
{
	String newObj=String(Impl->ToLower());

	return newObj;
}

String String::LTrim() const
{
	String newObj=String(Impl->LTrim());

	return newObj;
}

String String::RTrim() const
{
	String newObj=String(Impl->RTrim());

	return newObj;
}

String String::Trim() const
{
	String newObj=String(Impl->Trim());

	return newObj;
}

String String::LSet(unsigned int len, char c) const
{
	String newObj=String(Impl->LSet(len,c));

	return newObj;
}

String String::RSet(unsigned int len, char c) const
{
	String newObj=String(Impl->RSet(len,c));

	return newObj;
}

String String::StripExt() const
{
	String newObj=String(Impl->StripExt());

	return newObj;
}
String String::StripDir() const
{
	String newObj=String(Impl->StripDir());

	return newObj;
}
String String::ExtractExt() const 
{
	String newObj=String(Impl->ExtractExt());

	return newObj;
}
String String::ExtractDir() const
{
	String newObj=String(Impl->ExtractDir());

	return newObj;
}

String String::Read(const String& filename)
{
	String newobj=StringImp::Read((StringImp *)filename.mvar_ImpAcc);	

	return newobj;	
}

void String::Write(const String& filename, bool append ) const
{	
	Impl->Write((StringImp *)filename.mvar_ImpAcc,append);
}

