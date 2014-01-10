#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	IsometricMap* map = ResourceManager::Instance().LoadIsometricMap("data/isometric.tmx",0);	
	IsometricScene* scene = new IsometricScene(map);

	Image* imgcharac = ResourceManager::Instance().LoadImage("data/isoplayer.png",8,8);
	IsometricSprite* charac = scene->CreateSprite(imgcharac);	
	charac->SetPosition(map->GetTileWidth() * 1.5,0, map->GetTileHeight() * 1.5);
	charac->SetCollision(Sprite::COLLISION_RECT);
	charac->SetFPS(25);
	scene->GetCamera().FollowSprite(charac);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) 
	{		
		render.Clear();		

		if (screen.KeyPressed(GLFW_KEY_LEFT))
		{			
			charac->SetFrameRange(0,4);
			if (charac->GetCurrentFrame() > 4 )
				charac->SetCurrentFrame(0);
			charac->SetFPS(25);
			charac->MoveTo(charac->GetX() - map->GetTileWidth(),charac->GetY(),200);
			
		}
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))
		{
			charac->SetFrameRange(40,44);
			if (charac->GetCurrentFrame() < 40 || charac->GetCurrentFrame() > 44 )
				charac->SetCurrentFrame(40);
			charac->SetFPS(25);
			charac->MoveTo(charac->GetX() + map->GetTileWidth(),charac->GetY(),200);

		}
		else if (screen.KeyPressed(GLFW_KEY_UP))
		{
			charac->SetFrameRange(24,28);
			if (charac->GetCurrentFrame() < 24 || charac->GetCurrentFrame() > 28 )
				charac->SetCurrentFrame(24);
			charac->SetFPS(25);
			charac->MoveTo(charac->GetX(),charac->GetY() - map->GetTileHeight(),200);

		}
		else if (screen.KeyPressed(GLFW_KEY_DOWN))
		{
			charac->SetFrameRange(56,60);
			if (charac->GetCurrentFrame() < 56 || charac->GetCurrentFrame() > 60 )
				charac->SetCurrentFrame(56);
			charac->SetFPS(25);
			charac->MoveTo(charac->GetX(),charac->GetY() + map->GetTileHeight(), 200);

		}
		else	
			charac->SetFPS(0);					
			

		scene->Update(screen.ElapsedTime());
		scene->Render();
									
		screen.Refresh();
	}
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
