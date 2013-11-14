#ifndef ENTITY_H
#define ENTITY_H

class Entity
{		
	public:
		enum EEntityType
		{	EHero, EBullet, EEnemy, ERainDrop	};

		Entity();
		Entity(EEntityType eType, int iPosX, int iPosY, int iVel, char cGraph, int iColor, bool bAlive);		
		
		int GetX();			
		void SetX(int iX);
		int GetY();			
		void SetY(int iY);
		int GetVelocity();	
		void SetVelocity(int iVel);
		int GetColor();		
		void SetColor(int iColor);
		char GetGraphic();	
		void SetGraphic(char cGraph);
		bool IsAlive();		
		void SetAlive(bool bAlive);		
		EEntityType GetType();
		virtual void Run();

	protected:		
		int m_iPosX;
		int m_iPosY;
		int m_iVelocity;				
		int m_iColor;
		char m_cGraphic;
		bool m_bAlive;
		EEntityType m_eType;		
};

#endif