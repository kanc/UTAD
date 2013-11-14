#include "stdafx.h"
#include <list>
#include <string.h>

//predicado que devuelve cierto en caso de que la cadena contenga el caracter 'a'
bool contiene_caracter (const char *value) { return (strchr(value, 'a') != NULL); }

int _tmain(int argc, _TCHAR* argv[])
{
	//declaramos la lista de cadenas e insertamos elementos
	std::list<char *> milista;  
	
	milista.push_back("string 1");
	milista.push_back("otra cosita");
	milista.push_back("ole ole");
	milista.push_back("pajarito sin cola");

	//declaramos dos iteradores, uno para recorrer la lista y otro para el fin de la lista
	std::list<char *>::const_iterator l_it (milista.begin()), l_fin(milista.end());

	//mostramos las cadenas iniciales
	for(;l_it!=l_fin;++l_it) 					
		printf("cadena inicial: %s\n", *l_it);							
	
	//borramos las que contengan el caracter 'a'
	milista.remove_if(contiene_caracter);

	//inicilizamos el iterador
	l_it=milista.begin();

	//mostramos las cadenas resultantes
	for(;l_it!=l_fin;++l_it) 				
		printf("cadena post borrado: %s\n", *l_it);
		
	getchar();

	return 0;
}





