#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();

    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    //screen.Open(800, 600, false);

    Image* image = ResourceManager::Instance().LoadImage("data/images/alien1.png", 8);
    image->SetMidHandle();
	Sprite sprite(image);
    sprite.SetScale(6.0f, 6.0f);
    sprite.SetFPS(16);

    while ( screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC) ) {
		// Dibujamos el fondo
        renderer.Clear(55, 155, 255);

		// Dibujamos el alien
        sprite.SetPosition(screen.GetMouseX(), screen.GetMouseY());
        sprite.Update(screen.ElapsedTime());
        sprite.Render();

		// Refrescamos la pantalla
        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}
