#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Entity.h"

class World
{
	private:
		std::vector<Entity *> m_vEntities;
		int m_iTotalEntities;
		int m_iScore;
		Entity *m_pHero;
		Entity *m_pLBullet;
		Entity *m_pRBullet;

		void CheckCollisions();
		void GenerateEnemies();
		void GotoXY(int x, int y);
		void HideCursor(void);
		void CheckHeroBulletCollision (Entity *pEnemy);

	public:
		World();
		~World();

		void AddEntity(Entity *pEntity);
		void DeleteEntity(Entity *pEntity);
		void Render();
		void Run();
		bool EndGame();
		Entity * GetHero();
		Entity * GetLeftBullet();
		Entity * GetRigthBullet();
};

#endif