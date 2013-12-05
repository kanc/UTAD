#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"
#include "../include/rectcollision.h"

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();
    ResourceManager& resManager = ResourceManager::Instance();

    //screen.Open(640, 480, false);
    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);

    Font* font = resManager.LoadFont("data/fonts/font.png");
    CollisionPixelData* colPixelData = resManager.LoadCollisionPixelData("data/images/aliencol.png");
    Image* ballImg = resManager.LoadImage("data/images/ball.png");
    Image* boxImg = resManager.LoadImage("data/images/box.jpg");
    Image* circleImg = resManager.LoadImage("data/images/circle.png");
    Image* rectImg = resManager.LoadImage("data/images/rect.png");
    Image* alienImg = resManager.LoadImage("data/images/alien1.png", 8);
    ballImg->SetMidHandle();
    boxImg->SetMidHandle();
    circleImg->SetMidHandle();
    rectImg->SetMidHandle();
    alienImg->SetMidHandle();

	Scene scene;

    Sprite* sphereSprite = scene.CreateSprite(ballImg);
    sphereSprite->SetPosition(screen.GetWidth()/4, screen.GetHeight()/4);
    sphereSprite->SetScale(0.5f, 0.5f);
    sphereSprite->SetRadius(32);
    sphereSprite->SetCollision(Sprite::COLLISION_CIRCLE);

    Sprite* boxSprite = scene.CreateSprite(boxImg);
    boxSprite->SetPosition(screen.GetWidth()*3/4, screen.GetHeight()*3/4);
    boxSprite->SetScale(0.25f, 0.25f);
    boxSprite->SetCollision(Sprite::COLLISION_RECT);

    Sprite* alienSprite = scene.CreateSprite(alienImg);
    alienSprite->SetPosition(screen.GetWidth()/4, screen.GetHeight()*3/4);
    alienSprite->SetScale(4.0f, 4.0f);
    alienSprite->SetCollisionPixelData(colPixelData);
    alienSprite->SetCollision(Sprite::COLLISION_PIXEL);

    Sprite* pointerSprite = scene.CreateSprite(circleImg);
    pointerSprite->SetRadius(8);
    pointerSprite->SetCollisionPixelData(colPixelData);
    pointerSprite->SetCollision(Sprite::COLLISION_CIRCLE);

	int colMode = 1;
    while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) {
        if ( screen.MouseButtonPressed(0) ) {
			colMode = 1;
            pointerSprite->SetScale(1, 1);
            pointerSprite->SetImage(circleImg);
            pointerSprite->SetCollision(Sprite::COLLISION_CIRCLE);
		}
        if ( screen.MouseButtonPressed(1) ) {
			colMode = 2;
            pointerSprite->SetScale(1, 1);
            pointerSprite->SetImage(rectImg);
            pointerSprite->SetCollision(Sprite::COLLISION_RECT);
		}
        if ( screen.MouseButtonPressed(2) ) {
			colMode = 3;
            pointerSprite->SetScale(4, 4);
            pointerSprite->SetImage(alienImg);
            pointerSprite->SetCollision(Sprite::COLLISION_PIXEL);
		}

		// Actualizamos escena
        pointerSprite->SetPosition(screen.GetMouseX(), screen.GetMouseY());
        scene.Update(screen.ElapsedTime());
        if ( sphereSprite->CollisionSprite() )
            sphereSprite->SetColor(255, 0, 0, 255);
		else
            sphereSprite->SetColor(255, 255, 255, 255);
        if ( boxSprite->CollisionSprite() )
            boxSprite->SetColor(255, 0, 0, 255);
		else
            boxSprite->SetColor(255, 255, 255, 255);
        if ( alienSprite->CollisionSprite() )
            alienSprite->SetColor(255, 0, 0, 255);
		else
            alienSprite->SetColor(255, 255, 255, 255);

		// Dibujamos escena
        scene.Render();

		// Dibujamos texto de ayuda
        renderer.SetColor(0, 55, 255, 255);
        renderer.DrawText(font, "CLICK IZQUIERDO - ESFERA", 0, 0);
        renderer.DrawText(font, "CLICK DERECHO - CAJA", 0, 16);
        renderer.DrawText(font, "CLICK CENTRAL - PIXEL", 0, 32);
		switch ( colMode ) {
		case 1:
            renderer.DrawText(font, "MODO: ESFERA", 0, 48);
			break;
		case 2:
            renderer.DrawText(font, "MODO: CAJA", 0, 48);
			break;
		case 3:
            renderer.DrawText(font, "MODO: PIXEL", 0, 48);
			break;
		}

		// Refrescamos la pantalla
        screen.Refresh();
	}

    resManager.FreeResources();

	return 0;
}
