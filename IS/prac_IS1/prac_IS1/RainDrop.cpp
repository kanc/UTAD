#include "stdafx.h"
#include "Base.h"

RainDrop::RainDrop(char cGraph, bool bAlive)
{
	m_eType = ERainDrop;
	m_iPosX = GenerateX();
	m_iPosY = GenerateY();
	m_iVelocity = 0;
	m_cGraphic = cGraph;
	m_iColor = GenerateColor();
	m_bAlive = bAlive;
	m_iRebornTime = TIMETOREBORN;
	m_iLife = GenerateLife();
}

int RainDrop::GenerateX()
{
	int x;

	x = rand() % WORLDWIDTH;

	return x;
}

int RainDrop::GenerateY()
{
	int y;

	y = (rand() % (FLOORLINE - 2) + 1) ;

	return y;
}

int RainDrop::GenerateColor()
{
	int color;

	color= rand() % 3;

	switch (color)
	{
		case 0: color = 7; break;
		case 1: color = 8; break;
		case 2: color = 15; break;
	}

	return color;
}

int RainDrop::GenerateLife()
{
	int life;

	life = LIFEMIN + (rand() % LIFEMAX);	

	return life;
}

int RainDrop::GetRebornTime()
{
	return m_iRebornTime;
}

void RainDrop::SetRebornTime(int iReborn)
{
	m_iRebornTime = iReborn;
}

int RainDrop::GetLife()	
{
	return m_iLife;
}

void RainDrop::SetLife(int iLife)
{
	m_iLife = iLife;
}

void RainDrop::Run()
{
	m_iLife--;

	if (m_iLife == 0)
		m_bAlive=false;

	if (m_iLife <= (0 - m_iRebornTime))
	{
		m_bAlive = true;
		m_iPosX = GenerateX();
		m_iPosY = GenerateY();
		m_iColor = GenerateColor();
		m_iLife = GenerateLife();
	}
}
