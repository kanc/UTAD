#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	AudioEngine::Instance().Init();

	AudioBuffer wav = AudioBuffer("data/music.wav");
	AudioSource source = AudioSource(&wav);

	//TODO: Modificar el resourcemanager para cargar buffers de audio

	Listener::Instance().SetPosition(screen.GetWidth() / 2, screen.GetHeight() / 2, 0);

	float x,y;
	x = screen.GetWidth() / 2;
	y = screen.GetHeight() / 2;	

	while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) 
	{		
		render.Clear();

		source.SetPosition(x, y, 0);

		if (!source.IsPlaying())
			source.Play();
		
		if (screen.KeyPressed(GLFW_KEY_LEFT))
			x-=300 * screen.ElapsedTime();
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))
			x+=300 * screen.ElapsedTime();

		x = WrapValue(x, screen.GetWidth());		

		render.DrawEllipse(x,y,20,20);

        screen.Refresh();
	}

	source.Stop();

	AudioEngine::Instance().Finish();
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
