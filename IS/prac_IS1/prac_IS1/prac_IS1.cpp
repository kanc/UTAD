// Practica1.cpp : Defines the entry point for the console application.
//
/*#include "stdafx.h"
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include "Base.h"


struct Entity2
{
	enum EEntityType
	{ ECharacter, EBullet, EEnemy, EDrop };

	int m_iPosX;
	int m_iPosY;
	int m_iVelocity;
	bool m_bActive;
	int m_iLife;
	EEntityType m_eType;
	int m_iColor;

	Entity2();

	Entity2(EEntityType eType, int iIniPosX, int iIniPosY, int iVel, bool bActi = false, int iLife = 0, int iColor = 0)
	{
		m_iPosX = iIniPosX;
		m_iPosY = iIniPosY;
		m_iVelocity = iVel;
		m_bActive = bActi;		
		m_eType = eType;
		m_iLife = iLife;
		m_iColor=iColor;
	}
};

void UpdateWorld(char c);
void Draw();
void GotoXY(int x, int y);
void HideCursor(void);
void ProcessInput(char *c);
void IniWorld();
void CheckCollisions();
void GenerateEnemies();
void DeleteWorld();
Entity2 * CreateDrop();
void DrawDrops();

int g_iScore;
Entity2 *g_oLBullet, *g_oRBullet, *g_oLEnemy, *g_oREnemy, *g_oChar;
std::vector<Entity2 *> g_vEntities;

//int _tmain(int argc, _TCHAR* argv[])
int test()
{
	char *c=new char(1);

	HideCursor();

	IniWorld();
	
	while (*c != QUIT && g_oChar->m_bActive)
	{								
		ProcessInput(c);
		UpdateWorld(*c);		
		Draw();		

		Sleep(50);
	}	 	
	
	GotoXY(WORLDWIDTH/2,5);
	printf("G A M E    O V E R");

	getchar();

	DeleteWorld();

	return 0;
}

void DeleteWorld()
{
	delete g_oChar;
	delete g_oLBullet;
	delete g_oRBullet;
	delete g_oLEnemy;
	delete g_oREnemy;

	for (int i = NUMDROPS-1; i >= 0; i--)
	{
		delete g_vEntities[i];
		g_vEntities.pop_back();
	}
}

void IniWorld()
{
	g_iScore = 0;

	g_oChar    = new Entity2(Entity2::ECharacter, WORLDWIDTH/2,FLOORLINE,0,true);
	g_oLBullet = new Entity2(Entity2::EBullet, 0, FLOORLINE, -1,false);
	g_oRBullet = new Entity2(Entity2::EBullet, 0, FLOORLINE,  1,false);
	g_oLEnemy  = new Entity2(Entity2::EEnemy, 0, FLOORLINE,   1,false,4);
	g_oREnemy  = new Entity2(Entity2::EEnemy, 0,-FLOORLINE,  -1,false,4);	

	srand((unsigned int)time(0));

	for (int i = 0; i < NUMDROPS; i++)	
		g_vEntities.push_back( CreateDrop() );
	
}

Entity2 * CreateDrop()
{
	int x, y, life, color;	
	Entity2 *oNewDrop=NULL;
		
	y = rand() % (FLOORLINE - 2) + 1;
	x = rand() % WORLDWIDTH;
	life = rand() % LIFEMAX + 1;
	color= rand() % 3;

	switch (color)
	{
		case 0: color = 7; break;
		case 1: color = 8; break;
		case 2: color = 15; break;
	}
	
	oNewDrop=new Entity2(Entity2::EDrop,x,y,0,true,life,color);
	
	return oNewDrop;
}

void GenerateEnemies()
{
	if (!g_oLEnemy->m_bActive)
	{
		if (g_oLEnemy->m_iLife <= 0)
		{	
			g_oLEnemy->m_bActive=true;
			g_oLEnemy->m_iLife=5;
			g_oLEnemy->m_iPosX=WORLDBEGIN;
		}
	}

	if (!g_oREnemy->m_bActive)
	{
		if (g_oREnemy->m_iLife <= 0)
		{	
			g_oREnemy->m_bActive=true;
			g_oREnemy->m_iLife=5;
			g_oREnemy->m_iPosX=WORLDWIDTH;
		}
	}
}

void ProcessInput(char *c)
{
	*c = 0;

	if(_kbhit())		
		*c=_getch();
}

void UpdateWorld(char c)
{	
	if (c == KEYLEFT)		
		if (g_oChar->m_iPosX > 0)
			g_oChar->m_iPosX--;

	if (c == KEYRIGHT)
		if (g_oChar->m_iPosX <= WORLDWIDTH)
			g_oChar->m_iPosX++;	

	if (c == LEFTFIRE)
		if (!g_oLBullet->m_bActive)
		{	
			g_oLBullet->m_bActive=true;
			g_oLBullet->m_iPosX=g_oChar->m_iPosX-1;
		}		
			
	if (c == RIGHTFIRE)
		if (!g_oRBullet->m_bActive)
		{	
			g_oRBullet->m_bActive=true;
			g_oRBullet->m_iPosX=g_oChar->m_iPosX+1;
		}										

	if (g_oLBullet->m_bActive)	
		g_oLBullet->m_iPosX+=g_oLBullet->m_iVelocity;		

	if (g_oRBullet->m_bActive)
		g_oRBullet->m_iPosX+=g_oRBullet->m_iVelocity;

	if (g_oLEnemy->m_bActive)
		g_oLEnemy->m_iPosX+=g_oLEnemy->m_iVelocity;

	if (g_oREnemy->m_bActive)
		g_oREnemy->m_iPosX+=g_oREnemy->m_iVelocity;

	for (int i = 0; i < NUMDROPS; i++)
	{
		g_vEntities[i]->m_iLife--;		

		if (g_vEntities[i]->m_iLife == 0)
			g_vEntities[i]->m_bActive=false;	
		else if (g_vEntities[i]->m_iLife < (0 - TIMETOREBORN))
		{
			delete g_vEntities[i];
			g_vEntities[i]=CreateDrop();
		}
	}

	GenerateEnemies();
	CheckCollisions();

	if (!g_oLEnemy->m_bActive)
		g_oLEnemy->m_iLife--;

	if (!g_oREnemy->m_bActive)
		g_oREnemy->m_iLife--;

}

void CheckCollisions()
{
	if (g_oRBullet->m_iPosX > WORLDWIDTH)
		g_oRBullet->m_bActive=false;
	
	if (g_oLBullet->m_iPosX <= 0)
		g_oLBullet->m_bActive=false;

	if (g_oLBullet->m_bActive)
		if (g_oLBullet->m_iPosX < g_oLEnemy->m_iPosX)
		{
			g_oLBullet->m_bActive=false;
			g_oLEnemy->m_bActive=false;
			g_iScore++;
		}

	if (g_oRBullet->m_bActive)
		if (g_oRBullet->m_iPosX > g_oREnemy->m_iPosX)
		{
			g_oRBullet->m_bActive=false;
			g_oREnemy->m_bActive=false;
			g_iScore++;
		}

	if (g_oChar->m_iPosX == g_oLEnemy->m_iPosX || g_oChar->m_iPosX == g_oREnemy->m_iPosX)
		g_oChar->m_bActive=false;
}

void Draw()
{		
	DrawDrops();

	GotoXY(1,1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("Score: %i",g_iScore);	
	
	for (int i = 0; i <= WORLDWIDTH; i++)
	{				
		GotoXY(i,FLOORLINE);		

		if (i == g_oChar->m_iPosX)
		{	
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("X");
		}
		else if (i == g_oLBullet->m_iPosX && g_oLBullet->m_bActive)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("<");
		}
		else if (i == g_oRBullet->m_iPosX && g_oRBullet->m_bActive)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf(">");
		}
		
		else if (i == g_oREnemy->m_iPosX) 
				if (g_oREnemy->m_bActive)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					printf("O");
				}
				else				
				{	
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

					if (g_oREnemy->m_iLife % 2 == 0)
						printf("%c",197);
					else
						printf("X");
				}
				
		else if (i == g_oLEnemy->m_iPosX) 
				if (g_oLEnemy->m_bActive)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					printf("O");
				}
				else				
				{	
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

					if (g_oLEnemy->m_iLife % 2 == 0)
						printf("%c",197);
					else
						printf("X");
				}
		else
		{	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("_");
		}
	}	
	
}

void DrawDrops()
{
	for (int i = 0; i < NUMDROPS; i++)
	{
		GotoXY(g_vEntities[i]->m_iPosX,g_vEntities[i]->m_iPosY);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),g_vEntities[i]->m_iColor);

		if (g_vEntities[i]->m_bActive)		
			printf(".");
		else
			printf(" ");
	}
}

void GotoXY(int x, int y) 
{ 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void HideCursor(void) 
{
	HANDLE hdl;
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO t;
	t.bVisible = false;
	SetConsoleCursorInfo(hdl, &t);
}
*/

