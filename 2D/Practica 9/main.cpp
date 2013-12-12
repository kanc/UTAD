#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Image *img = ResourceManager::Instance().LoadImage("data/texture.png");	
	Emitter *emitter = new Emitter(img,true);

	emitter->SetAngularVelocity(0,360);
	emitter->SetLifetime(1,2);
	emitter->SetMaxColor(255,255,255);
	emitter->SetMinColor(0,0,0);
	emitter->SetRate(500,1000);
	emitter->SetVelocityX(-128,128);
	emitter->SetVelocityY(-128,128);	

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		if (screen.MouseButtonPressed(0))
			emitter->Start();
		else
			emitter->Stop();

		emitter->SetX(screen.GetMouseX());
		emitter->SetY(screen.GetMouseY());
		emitter->Update(screen.ElapsedTime());
		emitter->Render();

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
		
	return 0;
}

