#include "stdafx.h"
#include "Base.h"

World::World()
{
	m_iTotalEntities = 0;
	m_iScore = 0;
}

World::~World()
{
	for (int i = m_iTotalEntities-1; i >= 0 ; i--)
	{
		delete m_vEntities[i];
		m_vEntities.pop_back();
	}
}

void World::AddEntity(Entity *pEntity)
{
	m_vEntities.push_back(pEntity);
	m_iTotalEntities++;

	switch (pEntity->GetType())
	{
		case Entity::EHero:	
			m_pHero = pEntity;

			break;

		case Entity::EBullet:	
			if (pEntity->GetVelocity() < 0)	
				m_pLBullet = pEntity;	
			else	
				m_pRBullet = pEntity;	

			break;
	}
}

void World::DeleteEntity(Entity *pEntity)
{
	
}

void World::Render()
{
	//pintamos el suelo
	for (int i = WORLDBEGIN; i < WORLDWIDTH; i++)
	{	
		GotoXY(i,FLOORLINE);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
		printf("_");
	}

	//pintamos las entidades
	for (int i = 0; i < m_iTotalEntities; i++)
	{
		GotoXY(m_vEntities[i]->GetX(),m_vEntities[i]->GetY());		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),m_vEntities[i]->GetColor());

		if (m_vEntities[i]->IsAlive())		
			printf("%c",m_vEntities[i]->GetGraphic());		
		else 
		{
			if (m_vEntities[i]->GetType() == Entity::ERainDrop)
				printf(" ");

			if (m_vEntities[i]->GetType() == Entity::EEnemy)
				printf("%c",((Enemy *)m_vEntities[i])->GetGraphic());
		}

	}

	//pintamos la puntuacion
	GotoXY(1,1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("Score: %i",m_iScore);
	
}

void World::Run()
{
	for (int i = 0; i < m_iTotalEntities; i++)		
		m_vEntities[i]->Run();		

	CheckCollisions();
}

void World::CheckCollisions()
{
	for (int i = 0; i < m_iTotalEntities; i++)
	{
		if (m_vEntities[i]->GetType() == Entity::EEnemy)		
			CheckHeroBulletCollision(m_vEntities[i]);	
		
	}
}

void World::CheckHeroBulletCollision (Entity *pEnemy)
{
	if (pEnemy->IsAlive())
	{
		if (pEnemy->GetVelocity() > 0) //enemigo que viene por la izquierda
	
		{	if (pEnemy->GetX() > m_pHero->GetX())		
				m_pHero->SetAlive(false);
		
		if (pEnemy->GetX() > m_pLBullet->GetX() && m_pLBullet->IsAlive())
			{
				m_pLBullet->SetAlive(false);
				pEnemy->SetAlive(false);
				m_iScore++;
			}
		}
		else
		{
			if (pEnemy->GetX() < m_pHero->GetX())		
				m_pHero->SetAlive(false);
		
			if (pEnemy->GetX() < m_pRBullet->GetX() && m_pRBullet->IsAlive())
			{
				m_pRBullet->SetAlive(false);
				pEnemy->SetAlive(false);
				m_iScore++;
			}
		}
	}
}

bool World::EndGame()
{
	if (m_pHero->IsAlive())
		return false;
	else
		return true;	
}

void World::GotoXY(int x, int y) 
{ 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void World::HideCursor(void) 
{
	HANDLE hdl;
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO t;
	t.bVisible = false;
	SetConsoleCursorInfo(hdl, &t);
}

Entity * World::GetHero()
{
	return m_pHero;
}

Entity * World::GetLeftBullet()
{
	return m_pLBullet;
}

Entity * World::GetRigthBullet()
{
	return m_pRBullet;
}