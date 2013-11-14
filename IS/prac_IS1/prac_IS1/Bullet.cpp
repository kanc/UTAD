#include "stdafx.h"
#include "Base.h"

Bullet::Bullet(int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive)
{		
	m_eType = EBullet;
	m_iPosX = iPosX;
	m_iPosY = iPosY;
	m_iVelocity = iVel;
	m_cGraphic = cGraph;
	m_iColor = iColor;
	m_bAlive = bAlive;
}

void Bullet::Run()
{
	m_iPosX += m_iVelocity;

	CheckWorldCollision();
}

void Bullet::CheckWorldCollision()
{
	if (m_iVelocity < 0)	
	{	
		if (m_iPosX <= WORLDBEGIN ) //
			m_bAlive = false;		
	}
	else
	{	
		if (m_iPosX >= WORLDWIDTH) //
			m_bAlive = false;
	}
}
