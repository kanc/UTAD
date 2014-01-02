#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Map* mymap = new Map("data/map.tmx");
	Image* fondo = ResourceManager::Instance().LoadImage("data/parallax_background.jpg");
	Image* alien =  ResourceManager::Instance().LoadImage("data/alien.png");

	

	MapScene* scene = new MapScene(mymap,fondo);
	scene->SetAutoBackSpeed(0,0);
	scene->SetRelativeBackSpeed(-0.1,0);

	Sprite* sprAlien = scene->CreateSprite(alien);
	sprAlien->SetPosition(10,10);
	sprAlien->SetCollision(Sprite::CollisionMode::COLLISION_RECT);

	scene->GetCamera().FollowSprite(sprAlien);
	scene->GetCamera().SetBounds(0,0,mymap->GetWidth(), mymap->GetHeight());

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) 
	{		
		render.Clear();

		if (screen.KeyPressed(GLFW_KEY_LEFT))
			sprAlien->MoveTo(sprAlien->GetX() - 10, sprAlien->GetY(),60,60);

		if (screen.KeyPressed(GLFW_KEY_RIGHT))
			sprAlien->MoveTo(sprAlien->GetX() + 10, sprAlien->GetY(),60,60);

		if (screen.KeyPressed(GLFW_KEY_UP))
			sprAlien->MoveTo(sprAlien->GetX(), sprAlien->GetY() - 10,60, 60);

		if (screen.KeyPressed(GLFW_KEY_DOWN))
			sprAlien->MoveTo(sprAlien->GetX(), sprAlien->GetY() + 10,60, 60);

		scene->Update(screen.ElapsedTime());
		scene->Render();		
					
		screen.Refresh();
	}
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
