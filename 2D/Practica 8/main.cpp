#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);
	
	Image *backg =ResourceManager::Instance().LoadImage("data/backlayer.png");
	Image *front =ResourceManager::Instance().LoadImage("data/frontlayer.png");
	ParallaxScene *scene = new ParallaxScene(backg,front);

	scene->SetRelativeBackSpeed(0.8f,0.8f);
	scene->SetAutoBackSpeed(32,32);
	scene->SetRelativeFrontSpeed(1,1);
	scene->SetAutoFrontSpeed(-32,32);

	//scene->GetCamera().SetBounds(0,0,backg->GetWidth(),backg->GetHeight());
	
	Image *alien = ResourceManager::Instance().LoadImage("data/alien.png");
	alien->SetMidHandle();

	Sprite *sprite = scene->CreateSprite( alien );	

	scene->GetCamera().FollowSprite(sprite);

	sprite->SetX(100);		
	sprite->SetY(100);		

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		screen.SetTitle(String ("x: ") + String::FromFloat(sprite->GetX()) + " y: " + String::FromFloat(sprite->GetY()));

		render.Clear();

		//gestion de pulsacion de teclas
		if (screen.KeyPressed(GLFW_KEY_LEFT))
		{	
			sprite->SetX(sprite->GetX() - (120 * screen.ElapsedTime()));
			sprite->RotateTo(15,60);
		}
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))					
		{				
			sprite->SetX(sprite->GetX() + (120 * screen.ElapsedTime()));
			sprite->RotateTo(-15,60);
		}
		else if (screen.KeyPressed(GLFW_KEY_UP))											
			sprite->SetY(sprite->GetY() - (120 * screen.ElapsedTime()));
					
		else if (screen.KeyPressed(GLFW_KEY_DOWN))											
			sprite->SetY(sprite->GetY() + (120 * screen.ElapsedTime()));
			
		else
			sprite->RotateTo(0,60);
		
		
		scene->Update(screen.ElapsedTime());
		scene->Render();
		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
		
	return 0;
}

