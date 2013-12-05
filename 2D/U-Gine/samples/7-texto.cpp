#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"
#include <time.h>

#define TEXTO "Hola, mundo"

int main(int argc, char* argv[]) {
	srand(time(NULL));

    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();

    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    //screen.Open(800, 600, false);

    Font* font = ResourceManager::Instance().LoadFont("data/fonts/font.png");
    if ( !font ) screen.Close();

	int32 xspeed = 128 + rand()%128;
	int32 yspeed = 128 + rand()%128;
    float textx = rand()%(screen.GetWidth() - font->GetTextWidth(TEXTO));
    float texty = rand()%(screen.GetHeight() - font->GetTextHeight(TEXTO));
	uint8 r = rand()%256, g = rand()%256, b = rand()%256;
    while ( screen.IsOpened()  && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		// Actualizamos la posicion del texto
        textx += xspeed * screen.ElapsedTime();
        texty += yspeed * screen.ElapsedTime();
		if ( textx < 0 ) {
			textx = 0;
			xspeed *= -1;
			r = rand()%256;
			g = rand()%256;
			b = rand()%256;
        } else if ( textx > screen.GetWidth() - font->GetTextWidth(TEXTO) ) {
            textx = screen.GetWidth() - font->GetTextWidth(TEXTO);
			xspeed *= -1;
			r = rand()%256;
			g = rand()%256;
			b = rand()%256;
		}
		if ( texty < 0 ) {
			texty = 0;
			yspeed *= -1;
			r = rand()%256;
			g = rand()%256;
			b = rand()%256;
        } else if ( texty > screen.GetHeight() - font->GetTextHeight(TEXTO) ) {
            texty = screen.GetHeight() - font->GetTextHeight(TEXTO);
			yspeed *= -1;
			r = rand()%256;
			g = rand()%256;
			b = rand()%256;
		}

		// Limpiamos el fondo
        renderer.Clear(0, 0, 0);

		// Dibujamos el texto
        renderer.SetColor(r, g, b, 255);
        renderer.DrawText(font, TEXTO, textx, texty);

		// Refrescamos la pantalla
        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}
