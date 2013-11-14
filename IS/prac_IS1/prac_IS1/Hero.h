#ifndef HERO_H
#define HERO_H

#include "Entity.h"

class Hero : public Entity
{
	public:
		Hero(int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive);				

		virtual void Run();
};

#endif