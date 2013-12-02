#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);
		
	//Font *myFont = ResourceManager::Instance().LoadFont(String("data/monospaced.png"));
	Font *myFont = ResourceManager::Instance().LoadFont(String("data/arial16_2.png"));
	String texto = String("Hola Mundo!! vivo");
	double x,y, velx, vely;
	
	srand(time_t(10));

	velx = (rand() % 127) + 128;
	vely = (rand() % 127) + 128;

	x = 100;
	y = 100;
	
	render.SetColor(rand() % 255,rand() % 255,rand() % 255,255);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		x+=velx * screen.ElapsedTime();
		y+=vely * screen.ElapsedTime();				
		
		if (x + myFont->GetTextWidth(texto)  >= screen.GetWidth() || x <= 0)
		{	
			velx = velx * -1;
			render.SetColor(rand() % 255,rand() % 255,rand() % 255,255);
		}

		if (y + (myFont->GetTextHeight(texto)) >= screen.GetHeight() || y <= 0)
		{	vely = vely * -1;
			render.SetColor(rand() % 255,rand() % 255,rand() % 255,255);
		}
		
		myFont->Render(texto, x,y);

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
		
	return 0;
}

