#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

struct star
{
	int x;
	int y;
	int vel;

	star()
	{
		x = y = vel = 0;
	}
};

int main(int argc, char* argv[]) 
{
	Screen::Instance().Open(800, 600, false);
		
	int mousex = NULL;
	int mousey = NULL;
	int radius = 30;
	int lado = 50;
	double angle = 0;	
	star *estrellas[100];

	srand(time_t(0));

	for (int i = 0; i < 100; i++)
	{
		estrellas[i]=new star();
		estrellas[i]->x = rand() % 800;
		estrellas[i]->y = rand() % 600;
		estrellas[i]->vel = rand() % 3 + 1;
	}
	
	while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC) ) {

		double circlex, circley;

		mousex = Screen::Instance().GetMouseX();
		mousey = Screen::Instance().GetMouseY();
				
		circlex = mousex + DegCos(WrapValue(angle,360)) * radius;
		circley = mousey - (DegSin(WrapValue(angle,360)) * radius);

		angle+= Screen::Instance().ElapsedTime() * 360; //para que gire una vez por segundo

		//pintamos		
		Renderer::Instance().Clear();		

		for (int i = 50; i < 100; i++)				
		{	estrellas[i]->y += estrellas[i]->vel;
			Renderer::Instance().DrawPoint(estrellas[i]->x,estrellas[i]->y);

			if (estrellas[i]->y > 600) estrellas[i]->y = 0;
		}	

		Renderer::Instance().SetColor(0,255,0,0);
		Renderer::Instance().DrawRect(400 - lado/2, 300 -lado/2,lado,lado);

		Renderer::Instance().SetColor(0,0,255,0);
		Renderer::Instance().DrawRect(mousex - 5, mousey - 5,10,10);
		
		Renderer::Instance().SetColor(255,0,0,0);
		Renderer::Instance().DrawEllipse(circlex,circley,5,5);

		Screen::Instance().SetTitle(String("Angulo: ") + String::FromFloat(Angle(mousex,mousey,circlex,circley)) + String(" - Distancia: ") +  String::FromFloat(Distance(mousex,mousey,800/2, 600/2 )) );

		Renderer::Instance().SetColor(255,255,255,0);

		for (int i = 0; i < 50; i++)				
		{	estrellas[i]->y += estrellas[i]->vel;
			Renderer::Instance().DrawPoint(estrellas[i]->x,estrellas[i]->y);

			if (estrellas[i]->y > 600) estrellas[i]->y = 0;
		}	

		Screen::Instance().Refresh();
	}
	
	return 0;
}

