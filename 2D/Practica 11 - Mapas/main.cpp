#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Map* mymap = new Map("data/map.tmx");
	Image* fondo = ResourceManager::Instance().LoadImage("data/parallax_background.jpg");

	MapScene* scene = new MapScene(mymap,fondo);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) 
	{		
		render.Clear();

		scene->Update(screen.ElapsedTime());
		scene->Render();		
					
		screen.Refresh();
	}
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
