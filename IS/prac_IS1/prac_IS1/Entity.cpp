#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
	m_iPosX = 0;
	m_iPosY = 0;
	m_iVelocity = 0;
	m_cGraphic = 0;
	m_iColor = 0;
	m_bAlive = 0;
	m_eType = EHero;
}

Entity::Entity(Entity::EEntityType eType, int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive)
{
	m_iPosX = iPosX;
	m_iPosY = iPosY;
	m_iVelocity = iVel;
	m_cGraphic = cGraph;
	m_iColor = iColor;
	m_bAlive = bAlive;
	m_eType = eType;
}

void Entity::Run()
{

}

int Entity::GetX()
{
	return m_iPosX;
}

void Entity::SetX(int iX)
{
	m_iPosX = iX;
}

int Entity::GetY()
{
	return m_iPosY;
}

void Entity::SetY(int iY)
{
	m_iPosY = iY;
}

int Entity::GetVelocity()
{
	return m_iVelocity;
}

void Entity::SetVelocity(int iVel)
{
	m_iVelocity = iVel;
}

int Entity::GetColor()
{
	return m_iColor;
}

void Entity::SetColor(int iColor)
{
	m_iColor = iColor;
}

char Entity::GetGraphic()
{
	return m_cGraphic;
}

void Entity::SetGraphic(char cGraph)
{
	m_cGraphic=cGraph;
}

bool Entity::IsAlive()
{
	return m_bAlive;
}

void Entity::SetAlive(bool bAlive)
{
	m_bAlive = bAlive;
}

Entity::EEntityType Entity::GetType()
{
	return m_eType;
}

