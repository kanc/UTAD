#ifndef RAINDROP_H
#define RAINDROP_H

#include "Entity.h"

class RainDrop : public Entity
{
	private:
		int m_iRebornTime;
		int m_iLife;

		int GenerateX();
		int GenerateY();
		int GenerateColor();
		int GenerateLife();

	public:		
		RainDrop(char cGraph, bool bAlive);

		int GetRebornTime();	
		void SetRebornTime(int iReborn);				
		int GetLife();			
		void SetLife(int iLife);
		virtual void Run();
};

#endif