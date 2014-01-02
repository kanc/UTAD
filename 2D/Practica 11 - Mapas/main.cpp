#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Map* mymap = new Map("data/map2.tmx",1);
	Image* back = ResourceManager::Instance().LoadImage("data/back2.png");
	Image* front = ResourceManager::Instance().LoadImage("data/back1.png");
	Image* alien =  ResourceManager::Instance().LoadImage("data/alien.png");	

	MapScene* scene = new MapScene(mymap,back,front);
	scene->SetAutoBackSpeed(-5,0);
	scene->SetRelativeBackSpeed(0.5,0);
	scene->SetAutoFrontSpeed(0,0);
	scene->SetRelativeFrontSpeed(0.8,0);

	Sprite* sprAlien = scene->CreateSprite(alien);
	sprAlien->SetPosition(10,10);
	sprAlien->SetCollisionPixelData(new CollisionPixelData("data/aliencol.png"));	
	sprAlien->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);

	scene->GetCamera().FollowSprite(sprAlien);
	scene->GetCamera().SetBounds(0,0,mymap->GetWidth(), mymap->GetHeight());

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) 
	{		
		render.Clear();

		if (screen.KeyPressed(GLFW_KEY_LEFT))
			sprAlien->MoveTo(sprAlien->GetX() - 1, sprAlien->GetY(),60,60);

		if (screen.KeyPressed(GLFW_KEY_RIGHT))
			sprAlien->MoveTo(sprAlien->GetX() + 1, sprAlien->GetY(),60,60);

		if (screen.KeyPressed(GLFW_KEY_UP))
			sprAlien->MoveTo(sprAlien->GetX(), sprAlien->GetY() - 1,60, 60);

		if (screen.KeyPressed(GLFW_KEY_DOWN))
			sprAlien->MoveTo(sprAlien->GetX(), sprAlien->GetY() + 1,60, 60);

		scene->Update(screen.ElapsedTime());
		scene->Render();		
					
		screen.Refresh();
	}
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
