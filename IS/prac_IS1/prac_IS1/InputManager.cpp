#include "stdafx.h"
#include "InputManager.h"
#include "base.h"
#include <conio.h>

InputManager::InputManager()
{
	m_cInputChar = 0;
}

void InputManager::ReadInputKey()
{
	m_cInputChar = 0;

	if(_kbhit())		
		m_cInputChar =_getch();
}

char InputManager::GetInputKey()
{
	return m_cInputChar;
}

void InputManager::ManageHero(Entity *pHero)
{
	switch (m_cInputChar)
	{
		case KEYLEFT:	pHero->SetX(pHero->GetX() - pHero->GetVelocity());		break;
		case KEYRIGHT:	pHero->SetX(pHero->GetX() + pHero->GetVelocity());		break;
	}
}

void InputManager::ManageBullets(Entity *pLeftBullet, Entity *pRightBullet, Entity *pHero)
{
	switch (m_cInputChar)
	{
		case LEFTFIRE:
			if (!pLeftBullet->IsAlive())
			{
				pLeftBullet->SetAlive(true);
				pLeftBullet->SetX(pHero->GetX() - 1);
			}
			break;

		case RIGHTFIRE:
			if (!pRightBullet->IsAlive())
			{
				pRightBullet->SetAlive(true);
				pRightBullet->SetX(pHero->GetX() + 1);
			}
			break;
	}
		
}