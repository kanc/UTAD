#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

#define SPEED 128

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    ResourceManager& resManager = ResourceManager::Instance();

    //screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    screen.Open(800, 600, false);

    Image* image = resManager.LoadImage("data/images/alien1.png", 8);
    image->SetMidHandle();

    Image* backImg = resManager.LoadImage("data/images/background.png");
	Scene scene(backImg);

    Sprite* sprite = scene.CreateSprite(image);
    sprite->SetPosition(128, 128);
    sprite->SetScale(6.0f, 6.0f);
    sprite->SetFPS(16);

    Camera& camera = scene.GetCamera();
    camera.FollowSprite(sprite);
    camera.SetBounds(0, 0, backImg->GetWidth(), backImg->GetHeight());

	bool movingleft = false, movingright = false;
    while ( screen.IsOpened()  && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		// Actualizamos sprite
        if ( screen.KeyPressed(GLFW_KEY_LEFT) ) {
			movingleft = true;
            sprite->SetX(sprite->GetX() - (SPEED * screen.ElapsedTime()));
		} else
			movingleft = false;
        if ( screen.KeyPressed(GLFW_KEY_RIGHT) ) {
			movingright = true;
            sprite->SetX(sprite->GetX() + (SPEED * screen.ElapsedTime()));
		} else
			movingright = false;
        if ( screen.KeyPressed(GLFW_KEY_UP) ) sprite->SetY(sprite->GetY() - (SPEED * screen.ElapsedTime()));
        if ( screen.KeyPressed(GLFW_KEY_DOWN) ) sprite->SetY(sprite->GetY() + (SPEED * screen.ElapsedTime()));
		if ( movingleft )
            sprite->RotateTo(15, 90);
		else if ( movingright )
            sprite->RotateTo(-15, 90);
		else
            sprite->RotateTo(0, 90);

		// Actualizamos escena
        scene.Update(screen.ElapsedTime());
        scene.Render();

		// Refrescamos la pantalla
        screen.Refresh();
	}

    resManager.FreeResources();

	return 0;
}
