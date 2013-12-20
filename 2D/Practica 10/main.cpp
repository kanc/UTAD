#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Image* imgAlien = ResourceManager::Instance().LoadImage("data/alien.png");	
	Image* imgBall = ResourceManager::Instance().LoadImage("data/ball.png");	
	Image* imgBox = ResourceManager::Instance().LoadImage("data/box.jpg");
	Image* imgCircle = ResourceManager::Instance().LoadImage("data/circle.png");
	Image* imgRect = ResourceManager::Instance().LoadImage("data/rect.png");

	imgAlien->SetMidHandle();
	imgBall->SetMidHandle();
	imgBox->SetMidHandle();
	imgCircle->SetMidHandle();
	imgRect->SetMidHandle();

	Scene* myScene = new Scene();

	//Sprite* sprAlien = myScene->CreateSprite(imgAlien);
	Sprite* sprBox = myScene->CreateSprite(imgBox);
	Sprite* sprBall = myScene->CreateSprite(imgBall);
	Sprite* sprMousePos = myScene->CreateSprite(imgCircle);	

	sprBall->SetPosition(100,100);	
	sprBall->SetRadius(imgBall->GetWidth() /2);
	sprBall->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
	sprBox->SetPosition(screen.GetWidth() - 100, screen.GetHeight() - 100);
	sprBox->SetCollision(Sprite::CollisionMode::COLLISION_RECT);	

	sprMousePos->SetRadius(imgCircle->GetWidth() / 2);
	sprMousePos->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) 
	{		
		render.Clear();

		if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			sprMousePos->SetImage(imgCircle);
			sprMousePos->SetRadius(imgCircle->GetWidth() /2);
			sprMousePos->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
		}
		else if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_2))
		{
			sprMousePos->SetImage(imgRect);
			sprMousePos->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
		}

		sprMousePos->SetPosition(screen.GetMouseX(), screen.GetMouseY());		
		myScene->Update(screen.ElapsedTime());
		
		if (sprBall->CollisionSprite())
			sprBall->SetColor(255,0,0,125);
		else
			sprBall->SetColor(255,255,255,255);

		if (sprBox->CollisionSprite())
			sprBox->SetColor(255,0,0,125);
		else
			sprBox->SetColor(255,255,255,255);

		if (sprMousePos->CollisionSprite())
			sprMousePos->SetColor(255,0,0,125);
		else
			sprMousePos->SetColor(255,255,255,255);

		
		myScene->Render();				
		screen.Refresh();
	}
	ResourceManager::Instance().FreeResources();
		
	return 0;
}

