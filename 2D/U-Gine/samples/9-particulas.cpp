#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();
    ResourceManager& resManager = ResourceManager::Instance();

    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    //screen.Open(800, 600, false);

    Font* font = resManager.LoadFont("data/fonts/font.png");

    Image* image = resManager.LoadImage("data/images/star.png");
    image->SetMidHandle();

	Scene scene;

    Emitter* emitter = scene.CreateEmitter(image, true);

    emitter->SetRate(1, 1000);
    emitter->SetVelocityX(-128, 128);
    emitter->SetVelocityY(-128, 128);
    emitter->SetAngularVelocity(0, 360);
    emitter->SetLifetime(1, 2);

    Sprite* sprite = scene.CreateSprite(image, Scene::LAYER_FRONT);
    sprite->SetColor(255, 0, 0);

    while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) {
        sprite->SetPosition(screen.GetMouseX(), screen.GetMouseY());
        emitter->SetPosition(screen.GetMouseX(), screen.GetMouseY());
        if ( screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) )
            emitter->Start();
		else
            emitter->Stop();
		
        scene.Update(screen.ElapsedTime());
        scene.Render();

        renderer.SetBlendMode(Renderer::ALPHA);
        renderer.SetColor(255, 255, 0, 255);
        renderer.SetOrigin(0, 0);
        renderer.DrawText(font, "Pulse el boton izquierdo del raton para dibujar particulas", 0, 0);

        screen.Refresh();
	}

    resManager.FreeResources();

	return 0;
}
