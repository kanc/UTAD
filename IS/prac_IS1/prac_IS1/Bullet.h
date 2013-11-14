#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
	private:
		void CheckWorldCollision();

	public:
		Bullet(int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive);

		virtual void Run();
		
};

#endif