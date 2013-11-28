#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);
		
	Font text = Font(String("data/monospaced.png"));
	String texto = String("Hola MundoH");
	double x,y, velx, vely;
	char r,g,b;
	
	//velx = (rand() % 127) + 128;
	//vely = (rand() % 127) + 128;

	velx = 50;
	vely = 50;
	x= screen.GetWidth() /2;
	y= screen.GetHeight() /2;

	srand(time_t(0));

	render.SetColor(rand() % 255,rand() % 255,rand() % 255,255);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		x+=velx * screen.ElapsedTime();
		y+=vely * screen.ElapsedTime();		

		screen.SetTitle (String::FromFloat(x + text.GetTextWidth(texto)) + String(" ") + String::FromFloat(y));
		
		if (x + text.GetTextWidth(texto)  >= screen.GetWidth() || x <= 0)
		{	
			velx = velx * -1;
			render.SetColor(rand() % 255,rand() % 255,rand() % 255,255);
		}

		if (y + (text.GetTextHeight(texto)) >= screen.GetHeight() || y <= 0)
		{	vely = vely * -1;
			render.SetColor(rand() % 255,rand() % 255,rand() % 255,255);
		}
		
		text.Render(texto, x,y);

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}

