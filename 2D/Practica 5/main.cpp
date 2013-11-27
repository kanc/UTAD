#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Image *alien = ResourceManager::Instance().LoadImage("data/robin.png",5,5);
	Sprite *sprite = new Sprite(alien);

	sprite->SetX(100);
	sprite->SetY(100);
	sprite->SetFPS(150);
	sprite->SetBlendMode(Renderer::ALPHA);
	sprite->SetFrameRange(0,16);
	
	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		if (screen.KeyPressed(GL_LEFT))
			sprite->MoveTo(sprite->GetX() - 1,sprite->GetY(),1);

		if (screen.KeyPressed(GL_RIGHT))
			sprite->MoveTo(sprite->GetX() + 1,sprite->GetY(),1);

		
		sprite->Update(screen.ElapsedTime(),NULL);
		sprite->Render();

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}



