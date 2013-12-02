#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "include/InputManager.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();
	InputManager *im = new InputManager();

	screen.Open(800, 600, false);

	Image *imgalien = ResourceManager::Instance().LoadImage("data/alien.png");
	Sprite &alien = Sprite(imgalien);
	
	alien.SetX(100);
	alien.SetY(100);

	im->CreateVirtualButton(String("moveright"),eInputCode::Key_D);
	im->CreateVirtualButton(String("moveright"),eInputCode::Key_F);
	im->CreateVirtualButton(String("moveleft"),eInputCode::Key_A);
	im->CreateVirtualButton(String("moveup"),eInputCode::Key_W);
	im->CreateVirtualButton(String("movedown"),eInputCode::Key_S);
	im->CreateVirtualButton(String("pickmove"),eInputCode::Mouse_Button0);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		if (im->IsVirtualButtonPressed("moveright"))
			alien.MoveTo(alien.GetX() + 1, alien.GetY(),50);

		if (im->IsVirtualButtonPressed("moveleft"))
			alien.MoveTo(alien.GetX() - 1, alien.GetY(),50);

		if (im->IsVirtualButtonPressed("moveup"))
			alien.MoveTo(alien.GetX(), alien.GetY() - 1,50);

		if (im->IsVirtualButtonPressed("movedown"))
			alien.MoveTo(alien.GetX(), alien.GetY() + 1,50);

		if (im->IsVirtualButtonPressed("pickmove"))
			alien.MoveTo(screen.GetMouseX(),screen.GetMouseY(),50);

		alien.Update(screen.ElapsedTime(),NULL);
		alien.Render();

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}

