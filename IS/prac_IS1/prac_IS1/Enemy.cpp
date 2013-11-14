#include "stdafx.h"
#include "Base.h"

Enemy::Enemy(int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive,int iReborn)
{	
	m_eType = EEnemy;
	m_iPosX = iPosX;
	m_iPosY = iPosY;
	m_iVelocity = iVel;
	m_cGraphic = cGraph;
	m_iColor = iColor;
	m_bAlive = bAlive;
	m_iRebornTime = iReborn;
	m_iLife = iReborn;
}
					
void Enemy::Run()
{
	if (m_bAlive)
	{
		m_iPosX += m_iVelocity;	
		CheckWorldCollision();
	}
	else
		Regenerate();
}

void Enemy::Regenerate()
{
	if (!m_bAlive)
	{			
		m_iLife--;

		if (m_iLife == (0 - m_iRebornTime))
		{
			m_bAlive = true;
			m_iLife = m_iRebornTime;

			if (m_iVelocity > 0)
				m_iPosX = WORLDBEGIN;
			else
				m_iPosX = WORLDWIDTH;
		}
	}
}

void Enemy::CheckWorldCollision()
{
	if (m_iVelocity < 0)
		if (m_iPosX <= WORLDBEGIN)
		{
			m_bAlive = false;
			m_iPosX = WORLDWIDTH;
		}	
	else	
		if (m_iPosX >= WORLDWIDTH)
		{
			m_bAlive = false;
			m_iPosX = WORLDBEGIN;
		}	
}

unsigned char Enemy::GetGraphic()
{
	if (m_bAlive)
		return m_cGraphic;
	else 
	{
		if (m_iLife % 2 == 0)
			return 'X';
		else
			return 197;			
	}
}
