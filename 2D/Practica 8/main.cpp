#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);
	
	Image *backg =ResourceManager::Instance().LoadImage("data/background.png");
	Scene *scene = new Scene(backg);		
	//scene->GetCamera().SetBounds(0,0,backg->GetWidth(),backg->GetHeight());
	
	Sprite *sprite = scene->CreateSprite( ResourceManager::Instance().LoadImage("data/alien.png") );
	scene->GetCamera().FollowSprite(sprite);

	sprite->SetX(100);		
	sprite->SetY(100);		


	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		//gestion de pulsacion de teclas
		if (screen.KeyPressed(GLFW_KEY_LEFT))
		{	
			sprite->MoveTo(sprite->GetX() - 1,sprite->GetY(),50);
			sprite->RotateTo(15,30);
		}
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))					
		{				
			sprite->MoveTo(sprite->GetX() + 1,sprite->GetY(),50);
			sprite->RotateTo(-15,30);
		}		
		else
			sprite->RotateTo(0,30);	
		
		
		scene->Update(screen.ElapsedTime() * 3);
		scene->Render();
		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
		
	return 0;
}

