#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
	private:
		int m_iRebornTime;
		int m_iLife;

		void CheckWorldCollision();
		void Regenerate();

	public:
		Enemy(int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive,int iReborn);

		virtual unsigned char GetGraphic();
		virtual void Run();		

};

#endif