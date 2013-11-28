#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Image *alien = ResourceManager::Instance().LoadImage("data/alien.png");
	Image *pelotabasket = ResourceManager::Instance().LoadImage("data/ball.png");
	Image *pelotafutbol = ResourceManager::Instance().LoadImage("data/soccer_npot.png");

	Sprite *sprite = new Sprite(alien);
	Sprite *spBasket = new Sprite(pelotabasket);
	Sprite *spFutbol = new Sprite(pelotafutbol);

	sprite->SetX(400);
	sprite->SetY(300);	
	
	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		float mousex = screen.GetMouseX();
		float mousey = screen.GetMouseY();

		//gestion de pulsacion de teclas
		if (screen.KeyPressed(GLFW_KEY_LEFT))
		{	
			sprite->MoveTo(sprite->GetX() - 1,sprite->GetY(),60);
			sprite->RotateTo(15,30);
		}
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))					
		{				
			sprite->MoveTo(sprite->GetX() + 1,sprite->GetY(),60);
			sprite->RotateTo(-15,30);
		}		
		else
			sprite->RotateTo(0,30);

		//gestion de pulsacion de boton de raton
		if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{			
			render.DrawLine(sprite->GetX(),sprite->GetY(),mousex,mousey);
			sprite->MoveTo(mousex,mousey,150);

			double angle = DegATan2(mousey,mousex);

			if (mousex > sprite->GetX())
				angle = angle * -1;

			sprite->RotateTo(angle,(double)60);
		}
		
		//update y pintado de sprites
		sprite->Update(screen.ElapsedTime(),NULL);
		sprite->Render();

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}

/*function(t, b, c, d) {
	var ts=(t/=d)*t;
	var tc=ts*t;
	return b+c*(4*tc + -9*ts + 6*t);
}*/

