#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Image *alien = ResourceManager::Instance().LoadImage("data/alien.png");
	alien->SetMidHandle();

	Sprite *sprite = new Sprite(alien);

	sprite->SetX(400);
	sprite->SetY(300);
	sprite->SetFPS(15);
	sprite->SetBlendMode(Renderer::ALPHA);
	sprite->SetFrameRange(0,16);
	
	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		if (screen.KeyPressed(GLFW_KEY_LEFT))
		{	sprite->MoveTo(sprite->GetX() - 1,sprite->GetY(),-1);
			sprite->RotateTo(15,30);
		}
		else  if (screen.KeyPressed(GLFW_KEY_RIGHT))					
		{	
			sprite->MoveTo(sprite->GetX() + 1,sprite->GetY(),1);
			sprite->RotateTo(-15,30);
		}		
		else
			sprite->RotateTo(0,30);

		
		sprite->Update(screen.ElapsedTime(),NULL);
		sprite->Render();

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}



