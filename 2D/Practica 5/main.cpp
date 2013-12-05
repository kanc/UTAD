#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();
	float angle = 0;
	bool crece = true;

	screen.Open(800, 600, false);

	Image *alien = ResourceManager::Instance().LoadImage("data/alien.png");
	Image *pelotabasket = ResourceManager::Instance().LoadImage("data/ball.png");
	Image *pelotafutbol = ResourceManager::Instance().LoadImage("data/soccer_npot.png");

	Sprite *sprite = new Sprite(alien);
	Sprite *spBasket = new Sprite(pelotabasket);
	Sprite *spFutbol = new Sprite(pelotafutbol);

	sprite->SetX(400);
	sprite->SetY(300);	

	spBasket->SetX(300);
	spBasket->SetY(200);			

	spFutbol->SetX(600);
	spFutbol->SetY(400);	
	
	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		float mousex = screen.GetMouseX();
		float mousey = screen.GetMouseY();

		//gestion de pulsacion de teclas
		if (screen.KeyPressed(GLFW_KEY_LEFT))
		{	
			sprite->MoveTo(sprite->GetX() - 1,sprite->GetY(),90);
			sprite->RotateTo(15,30);
		}
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))					
		{				
			sprite->MoveTo(sprite->GetX() + 1,sprite->GetY(),90);
			sprite->RotateTo(-15,30);
		}		
		else
			sprite->RotateTo(0,30);
		
		//gestion de pulsacion de boton de raton
		if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{						
			sprite->MoveTo(mousex,mousey,150);

			double angle = DegATan2(mousey,mousex);

			if (mousex > sprite->GetX())
				angle = angle * -1;

			sprite->RotateTo(angle,(double)60);
		}
		
		//escalado de los sprites
		if (crece)
		{	if (!spBasket->IsScaling())
			{	
				spBasket->ScaleTo(0.5f,0.5f,5);
				crece = false;
			}
			if (!spFutbol->IsScaling())
			{	
				spFutbol->ScaleTo(5,5,3);
				crece = false;
			}
		}
		else
		{	if (!spBasket->IsScaling())
			{	
				spBasket->ScaleTo(5,5,5);
				crece = true;
			}
			if (!spFutbol->IsScaling())
			{	
				spFutbol->ScaleTo(0.5f,0.5f,3);
				crece = true;
			}
		}
		
		//rotacion de los sprites
		spFutbol->RotateTo(WrapValue(angle,360),30);
		spBasket->RotateTo(WrapValue(angle,360),30);

		angle++;

		//update y pintado de sprites
		sprite->Update(screen.ElapsedTime(),NULL);
		spBasket->Update(screen.ElapsedTime(),NULL);
		spFutbol->Update(screen.ElapsedTime(),NULL);
		spBasket->Render();
		spFutbol->Render();
		sprite->Render();

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}

