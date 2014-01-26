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

	float x,y,pitch;
	x = screen.GetWidth() / 2;
	y = screen.GetHeight() / 2;
	pitch = 1;

	source.SetGain(2);

	Font* fuente = ResourceManager::Instance().LoadFont("data/arial16_2.png");
	
	while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) 
	{		
		render.Clear();

		source.SetPosition(x, y, 0);
		source.SetPitch(pitch);

		if (!source.IsPlaying())
			source.Play();
		
		if (screen.KeyPressed(GLFW_KEY_LEFT))
			x-=50 * screen.ElapsedTime();
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))
			x+=50 * screen.ElapsedTime();
		else if (screen.KeyPressed(GLFW_KEY_UP))
			pitch+= screen.ElapsedTime();
		else if (screen.KeyPressed(GLFW_KEY_DOWN))
			pitch-= screen.ElapsedTime();
		else if (screen.KeyPressed(GLFW_KEY_SPACE))
		{
			x = screen.GetWidth() / 2;
			pitch = 1;
		}

		x = WrapValue(x, screen.GetWidth());		

		render.DrawEllipse(x,y,10,10);

		render.DrawText(fuente, String("cursor izquierda : desplazar fuente a la izquierda"),10,10);
		render.DrawText(fuente, String("cursor derecha : desplazar fuente a la derecha"),10,30);
		render.DrawText(fuente, String("cursor arriba : aumentar pitch"),10,50);
		render.DrawText(fuente, String("cursor abajo : disminuir pitch"),10,70);
		render.DrawText(fuente, String("espacio : resetear pitch y posicion"),10,90);
		render.DrawText(fuente, String("pitch: ") + String::FromFloat(pitch),10,110);
		render.DrawText(fuente, String("(Listener)"),(screen.GetWidth() / 2) - fuente->GetTextWidth(String("(Listener)")) / 2,  screen.GetHeight() / 2 + 20);
        screen.Refresh();
	}

	source.Stop();

	AudioEngine::Instance().Finish();
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
