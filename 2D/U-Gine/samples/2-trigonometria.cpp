#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();

    //screen.Open(640, 480, false);
    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);

    Font* font = ResourceManager::Instance().LoadFont("data/fonts/font.png");
	
	float ang = 0;
    while ( screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC) ) {
		// Borramos fondo
        renderer.Clear(0, 0, 0);

		// Pintamos cuadrado en el centro de la pantalla
        renderer.SetColor(0, 255, 0, 255);
        renderer.DrawRect(screen.GetWidth()/2 - 16, screen.GetHeight()/2 - 16, 32, 32);
		
		// Pintamos puntero del raton
        renderer.SetColor(0, 0, 255, 255);
        renderer.DrawRect(screen.GetMouseX()-8, screen.GetMouseY()-8, 16, 16);

		// Pintamos esfera con movimiento circular
		ang += 0.5;
        float xpos = screen.GetMouseX() + DegCos(ang)*64;
        float ypos = screen.GetMouseY() - DegSin(ang)*64;
        renderer.SetColor(255, 0, 0, 255);
        renderer.DrawEllipse(xpos, ypos, 16, 16);

		// Actualizamos texto con la informacion
        String text = String("Angulo=") + String::FromInt(Angle(screen.GetMouseX(), screen.GetMouseY(), xpos, ypos)).LSet(3, "0").RSet(12, " ");
        text += String("Distancia=") + String::FromFloat(Distance(screen.GetMouseX(), screen.GetMouseY(), screen.GetWidth()/2, screen.GetHeight()/2));
        renderer.SetColor(255, 255, 0, 255);
        renderer.DrawText(font, text, 0, 0);
        //screen.SetTitle(text);

		// Refrescamos la pantalla
        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}
