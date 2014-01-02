#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    ResourceManager& resManager =  ResourceManager::Instance();

    //screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    screen.Open(800, 600, false);

    Image* characterImg = resManager.LoadImage("data/images/character.png", 16);
    Image* backImg = resManager.LoadImage("data/images/clouds.png");
    Map* map = resManager.LoadMap("data/maps/map.tmx");

    characterImg->SetHandle(characterImg->GetWidth()/2, characterImg->GetHeight());
	
	MapScene scene(map, backImg, backImg);
    scene.SetBackgroundColor(0, 155, 255);
    scene.SetRelativeBackSpeed(0.6, 0.6);
    scene.SetRelativeFrontSpeed(0.8, 0.8);
    scene.SetAutoBackSpeed(-4, 2);
    scene.SetAutoFrontSpeed(-6, 3);

    Sprite* character = scene.CreateSprite(characterImg);
    character->SetFrameRange(0, 8);
    character->SetPosition(192, 400);
    character->SetCollision(Sprite::COLLISION_RECT);

    Camera& cam = scene.GetCamera();
    cam.SetBounds(0, 0, scene.GetMap()->GetWidth(), scene.GetMap()->GetHeight());
    cam.FollowSprite(character);

	double gravity = 10;
    while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) {
		// Actualizamos movimiento del jugador
        double toX = character->GetX();
        if ( screen.KeyPressed(GLFW_KEY_LEFT) ) {
			toX = -10000;
            character->SetScale(-1, 1);
        } else if ( screen.KeyPressed(GLFW_KEY_RIGHT) ) {
			toX = 10000;
            character->SetScale(1, 1);
		}
        character->MoveTo(toX, character->GetY() + gravity, 256, 512);

		// Calculamos distancia al suelo
        double distanceToFloor = Distance(character->GetX(), character->GetY(), character->GetX(), scene.GetMap()->GetGroundY(character->GetX(), character->GetY()));

		// Salto del jugador
        if ( screen.KeyPressed(GLFW_KEY_SPACE) && distanceToFloor < 10 )
			gravity = -48;

		// Actualizamos gravedad
        gravity += 128 * screen.ElapsedTime();
		if ( gravity > 10 )
            gravity = 10;
		
		// Actualizamos escena
        scene.Update(screen.ElapsedTime());

		// Actualizamos animacion del jugador
        if ( character->IsMoving() ) {
			if ( distanceToFloor < 10 ) {
                character->SetFPS(16);
			} else {
                character->SetFPS(0);
                character->SetCurrentFrame(1);
			}
		} else {
            character->SetFPS(0);
            character->SetCurrentFrame(0);
        }

		// Dibujamos
        scene.Render();
        screen.Refresh();
	}

    resManager.FreeResources();

	return 0;
}