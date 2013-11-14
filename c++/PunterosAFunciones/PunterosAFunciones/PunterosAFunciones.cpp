#include "stdafx.h"
#include <conio.h>
#include <Windows.h>

struct Entity;

//definimos nuestro typedef llamado FuncEntity y que hace referencia a una funcion que devuelve un puntero a void y 
//recibe un puntero de tipo Entity
typedef void(*FuncEntity)(Entity *entidad);

const int UPDATE=0;
const int DRAW=1;

//definimos nuestra estructura
struct Entity
{
	unsigned int m_x;
	unsigned int m_y;
	int m_incrementoX;
	int m_incrementoY;
	int salto;
	bool subiendo;
	bool bajando;

	FuncEntity *funcion;

	//constructor de la estructura
	Entity(unsigned int x, unsigned int y, FuncEntity *funcs, int increX, int increY)
	{
		m_x=x;
		m_y=y;
		m_incrementoX= increX;
		m_incrementoY= increY;
		funcion=funcs;
		salto=0;
		subiendo=true;
	}
};

//funciones auxiliares
void gotoxy(int x, int y);
void hidecursor(void);
void clear();

//funciones de las entidades
void updateHuman(Entity *entidad);
void updateHorse(Entity *entidad);
void updateBird(Entity *entidad);
void drawHuman(Entity *entidad);
void drawHorse(Entity *entidad);
void drawBird(Entity *entidad);

//tablas de funciones de tipo Entity (puntero a funcion que devuelve void * y recibe un Entity *
FuncEntity tablaHumans[2];
FuncEntity tablaHorses[2];
FuncEntity tablaBirds[2];

int _tmain(int argc, _TCHAR* argv[])
{
	//asignamos las referencias de las funciones a las posiciones de la tabla
	tablaHumans[UPDATE]=&updateHuman;
	tablaHumans[DRAW]=&drawHuman;
	tablaHorses[UPDATE]=&updateHorse;
	tablaHorses[DRAW]=&drawHorse;
	tablaBirds[UPDATE]=&updateBird;
	tablaBirds[DRAW]=&drawBird;

	//iniciamos las entidades
	Entity humano(10,10,tablaHumans,1,0);
	Entity caballo(15,15,tablaHorses,1,1);
	Entity caballo2(11,11,tablaHorses,2,2);
	Entity caballo3(30,5,tablaHorses,0,1);
	Entity pajaro(20,20,tablaBirds,1,1);
	Entity pajaro2(5,5,tablaBirds,2,2);

	while (1)
	{
		//update de las entidades
		(*humano.funcion[UPDATE])(&humano);
		(*caballo.funcion[UPDATE])(&caballo);
		(*caballo2.funcion[UPDATE])(&caballo2);
		(*caballo3.funcion[UPDATE])(&caballo3);
		(*pajaro.funcion[UPDATE])(&pajaro);
		(*pajaro2.funcion[UPDATE])(&pajaro2);
		
		//limpiar la pantalla
		clear();

		//pintar las entidades
		(*humano.funcion[DRAW])(&humano);
		(*caballo.funcion[DRAW])(&caballo);
		(*caballo2.funcion[DRAW])(&caballo2);
		(*caballo3.funcion[DRAW])(&caballo3);
		(*pajaro.funcion[DRAW])(&pajaro);
		(*pajaro2.funcion[DRAW])(&pajaro2);

	}

	return 0;
}

void updateBird(Entity *entidad)
{
	if (entidad->m_x >= 80)
		entidad->m_incrementoX=-entidad->m_incrementoX;

	if (entidad->m_x <= 0)
		entidad->m_incrementoX=entidad->m_incrementoX;

	if (entidad->m_y <= 0)
		entidad->m_incrementoY=entidad->m_incrementoY;

	if (entidad->m_y >= 25)
		entidad->m_incrementoY=-entidad->m_incrementoY;

	entidad->m_x+=entidad->m_incrementoX;
	entidad->m_y+=entidad->m_incrementoY;
	
}

void updateHorse(Entity *entidad)
{
	if (entidad->salto >=10)
	{	entidad->m_incrementoY=-1;		
		entidad->bajando=true;
		entidad->subiendo=false;
	}
	
	if (entidad->salto <=0)
	{	entidad->m_incrementoY=1;
		entidad->bajando=false;
		entidad->subiendo=true;
	}

	if (entidad->subiendo)
		entidad->salto++;
	else
		entidad->salto--;

	if (entidad->m_x >= 80)
		entidad->m_x=0;

	entidad->m_y+=entidad->m_incrementoY;
	entidad->m_x+=entidad->m_incrementoX;
	
	
}

void updateHuman(Entity *entidad)
{
	entidad->m_x+=entidad->m_incrementoX;
	
	if (entidad->m_x > 80)
		entidad->m_x=0;
	
}
void drawHuman(Entity *entidad)
{
	gotoxy(entidad->m_x,entidad->m_y);
	printf("%s","(O_O)");
}
void drawBird(Entity *entidad)
{
	gotoxy(entidad->m_x,entidad->m_y);
	printf("%s","-(ovo)-");
}
void drawHorse(Entity *entidad)
{
	gotoxy(entidad->m_x,entidad->m_y);
	printf("%s","nnP");
}



void gotoxy(int x, int y) 
{ 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void hidecursor(void) {
	HANDLE hdl;
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO t;
	t.bVisible = false;
	SetConsoleCursorInfo(hdl, &t);
}

void clear()
{
	system("cls");
}

/*
Crear un sistema de entidades con las siguientes características.

1.- Crear una estructura entidad genérica.
2.- La estructura entidad contendrá un posición (x, y) en el mundo.
3.- La estructura entidad contendrá una tabla de funciones:
		*) La primera entrada en la tabla de funciones será la función "Update"
		*) La segunda entrada en la tabla de funciones será la función "Draw"

4.- En la creación de la entidad se le pasará la posicion (x,y) inicial y la tabla de funciones.

5.- Se crearan diferentes funciones de "Update" cada una de ellas actualizará la posición de la entidad en el mundo 
    de una manera diferente, por ejemplo:
			UpdateHuman, UpdateHorse, UpdateBird, UpdateDolphin
6.- Se crearan diferentes funciones de "Draw" cada una de ellas pintará la entidad en el mundo de una manera diferente, por ejemplo:
			DrawSquare, DrarLineH, DrawLineV, DrawPoint
			
7.- Se crearan un conjunto de entidades con diferentes combinaciones de las funciones anteriores.
8.- Se creará un bucle principal en el que se ejecutará:
	*) El update de todas las entidades.
	*) Se limpiará la pantalla.
	*) El pintado de todas las entidades.
	
9.- Del programa se saldrá cuando el jugador de a la tecla de "ESC"

10.- Opcinalmente:
	*) Se podrá manejar una entidad por la pantalla con las teclas.
	
11.- Para hacer la práctica se pueden utilizar las siguientes funciones:
   *) Se necesita incluir: <windows.h>
// ***************************************************************************************
// FUNCIONES AUXILIARES DE PINTADO
// ***************************************************************************************
void gotoxy(int x, int y) 
{ 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void hidecursor(void) {
	HANDLE hdl;
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO t;
	t.bVisible = false;
	SetConsoleCursorInfo(hdl, &t);
}

void clear()
{
	system("cls");
}

	*) Se necesita incluir: <conio.h>
	kbhit, getch
	*/