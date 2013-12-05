#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

#define RADIUS 32

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();

    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    //screen.Open(800, 600, false);

    Font* font = ResourceManager::Instance().LoadFont("data/fonts/font.png");

    while ( screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC) ) {
		// Limpiamos fondo de pantalla
        renderer.Clear(0, 0, 0);
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawRect(screen.GetWidth()/3, 0, screen.GetWidth()/3, screen.GetHeight());

		// Dibujamos modo SOLID
        int32 halfx = screen.GetWidth()/2;
        int32 halfy = screen.GetHeight()/4;
        renderer.SetBlendMode(Renderer::SOLID);
        renderer.SetColor(255, 0, 0, 128);
        renderer.DrawEllipse(halfx, halfy-RADIUS, RADIUS, RADIUS);
        renderer.SetColor(0, 255, 0, 128);
        renderer.DrawEllipse(halfx-RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetColor(0, 0, 255, 128);
        renderer.DrawEllipse(halfx+RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetBlendMode(Renderer::ALPHA);
        renderer.SetColor(0, 0, 0, 255);
        renderer.DrawText(font, "SOLID", halfx - font->GetTextWidth("SOLID")/2, halfy + RADIUS*2);

		// Dibujamos modo ALPHA
        halfx = screen.GetWidth()/6;
        halfy = screen.GetHeight()/2;
        renderer.SetBlendMode(Renderer::ALPHA);
        renderer.SetColor(255, 0, 0, 128);
        renderer.DrawEllipse(halfx, halfy-RADIUS, RADIUS, RADIUS);
        renderer.SetColor(0, 255, 0, 128);
        renderer.DrawEllipse(halfx-RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetColor(0, 0, 255, 128);
        renderer.DrawEllipse(halfx+RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawText(font, "ALPHA", halfx - font->GetTextWidth("ALPHA")/2, halfy + RADIUS*2);

		// Dibujamos modo MULTIPLICATIVE
        halfx = screen.GetWidth()/2;
        halfy = screen.GetHeight()*3/4;
        renderer.SetBlendMode(Renderer::MULTIPLICATIVE);
        renderer.SetColor(255, 0, 0, 255);
        renderer.DrawEllipse(halfx, halfy-RADIUS, RADIUS, RADIUS);
        renderer.SetColor(0, 255, 0, 255);
        renderer.DrawEllipse(halfx-RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetColor(0, 0, 255, 255);
        renderer.DrawEllipse(halfx+RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetBlendMode(Renderer::ALPHA);
        renderer.SetColor(0, 0, 0, 255);
        renderer.DrawText(font, "MULTIPLICATIVE", halfx - font->GetTextWidth("MULTIPLICATIVE")/2, halfy + RADIUS*2);

		// Dibujamos modo ADDITIVE
        halfx = screen.GetWidth()*5/6;
        halfy = screen.GetHeight()/2;
        renderer.SetBlendMode(Renderer::ADDITIVE);
        renderer.SetColor(255, 0, 0, 255);
        renderer.DrawEllipse(halfx, halfy-RADIUS, RADIUS, RADIUS);
        renderer.SetColor(0, 255, 0, 255);
        renderer.DrawEllipse(halfx-RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetColor(0, 0, 255, 255);
        renderer.DrawEllipse(halfx+RADIUS/2, halfy, RADIUS, RADIUS);
        renderer.SetBlendMode(Renderer::ALPHA);
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawText(font, "ADDITIVE", halfx - font->GetTextWidth("ADDITIVE")/2, halfy + RADIUS*2);

		// Refrescamos la pantalla
        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}
