#include "stdafx.h"
#include "Base.h"

void InitWorld();

World *g_pWorld;
InputManager *g_pInput;

int _tmain(int argc, _TCHAR* argv[])
{
	InitWorld();

	while (!g_pWorld->EndGame())
	{
		g_pInput->ReadInputKey();
		g_pInput->ManageHero(g_pWorld->GetHero());
		g_pInput->ManageBullets(g_pWorld->GetLeftBullet(), g_pWorld->GetRigthBullet(), g_pWorld->GetHero());
		g_pWorld->Run();
		g_pWorld->Render();

		Sleep(50);
	}

	delete g_pWorld;
	delete g_pInput;

	return 0;
}

void InitWorld()
{
	g_pWorld = new World();
	g_pInput = new InputManager();

	g_pWorld->AddEntity(new Hero (WORLDWIDTH/2, FLOORLINE, 1,'X', 7, true));
	g_pWorld->AddEntity(new Bullet(0, FLOORLINE, -1, '<', 14, false));
	g_pWorld->AddEntity(new Bullet(0, FLOORLINE,  1, '>', 14, false));
	g_pWorld->AddEntity(new Enemy(WORLDBEGIN, FLOORLINE,  1, 'O', 12, true, TIMETOREBORN));
	g_pWorld->AddEntity(new Enemy(WORLDWIDTH, FLOORLINE, -1, 'O', 12, true, TIMETOREBORN));

	for (int i = 0; i < NUMDROPS; i++)	
		g_pWorld->AddEntity(new RainDrop('.', true));
}
