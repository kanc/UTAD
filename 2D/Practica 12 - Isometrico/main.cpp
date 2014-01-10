#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	IsometricMap* map = ResourceManager::Instance().LoadIsometricMap("data/isometric.tmx",0);
	//Map* map = ResourceManager::Instance().LoadMap("data/isometric.tmx",0);
	IsometricScene* scene = new IsometricScene(map);
	//MapScene* scene = new MapScene(map);

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
