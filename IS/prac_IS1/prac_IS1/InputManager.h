#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Entity.h"

class InputManager
{
	private:
		char m_cInputChar;

	public:
		InputManager();

		void ReadInputKey();
		char GetInputKey();
		void ManageHero(Entity *pEnt);
		void ManageBullets(Entity *pLeftBullet, Entity *pRightBullet, Entity *pHero);
};

#endif