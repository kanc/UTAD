#include "stdafx.h"
#include "Hero.h"

Hero::Hero(int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive)
{	
	m_eType = EHero;
	m_iPosX = iPosX;
	m_iPosY = iPosY;
	m_iVelocity = iVel;
	m_cGraphic = cGraph;
	m_iColor = iColor;
	m_bAlive = bAlive;
}

void Hero::Run()
{

}
