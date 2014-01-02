#include "stdafx.h"
#include "String.h"


int _tmain(int argc, _TCHAR* argv[])
{
	String test=String("c:\\david\\mifichero.txt");	
	String fichero=String("test.txt");	
	String test2=String("          largo es una bonita palabra que alargo siempre que puedo decir largo de aqui mismo tio        ");			
	String test3=String("larguisimo");
	int i;
	char c='a';	

	String j = String::FromInt(45);

	printf("%s",j.ToCString());

	getchar();

	i=test2.Find(test,5);
	
	c=(test)[50];
	
	printf("%s\n ",(test2.Replace(test,test3)).ToCString());	

	printf("%s",(test.ExtractExt()).ToCString());	

	if (test>test2)
		printf("1 mayor");
	else
		printf("1 menor");

	printf("fichero: %s", (String::Read(fichero)).ToCString());

	test2.Write(test);

	getchar();

	return 0;
}

