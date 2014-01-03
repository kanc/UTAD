#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	Map* mymap = new Map("data/map2.tmx",1);
	Image* back = ResourceManager::Instance().LoadImage("data/back2.png");
	Image* front = ResourceManager::Instance().LoadImage("data/back1.png");
	Image* alien =  ResourceManager::Instance().LoadImage("data/alienanim.png",8,1);	
	alien->SetMidHandle();

	MapScene* scene = new MapScene(mymap,back,front);
	scene->SetAutoBackSpeed(-5,0);
	scene->SetRelativeBackSpeed(0.5,0);
	scene->SetAutoFrontSpeed(0,0);
	scene->SetRelativeFrontSpeed(0.8,0);

	Sprite* sprAlien = scene->CreateSprite(alien);
	sprAlien->SetPosition(10,10);
	sprAlien->SetFPS(16);
	sprAlien->SetCurrentFrame(1);
	sprAlien->SetFrameRange(1,20);
	sprAlien->SetCollisionPixelData(new CollisionPixelData("data/aliencol.png"));	
	sprAlien->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
	sprAlien->SetScale(3,3);	

	scene->GetCamera().FollowSprite(sprAlien);
	scene->GetCamera().SetBounds(0,0,mymap->GetWidth(), mymap->GetHeight());

	bool jump = false;
	float vel = 0, grav = 10;

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) 
	{		
		render.Clear();

		double destX = sprAlien->GetX();

        if ( screen.KeyPressed(GLFW_KEY_LEFT) ) 
			destX = sprAlien->GetX() - 10;            
        else if ( screen.KeyPressed(GLFW_KEY_RIGHT) ) 
			destX = sprAlien->GetX() + 10;

		sprAlien->MoveTo(destX, sprAlien->GetY() - vel + grav, 200, 500);
		float distance = mymap->GetGroundY(sprAlien->GetX(), sprAlien->GetY()) -  (sprAlien->GetY() + sprAlien->GetImage()->GetHeight());

		screen.SetTitle(String::FromFloat(distance));

		if ((-vel + grav) > 0 && distance < 13) sprAlien->SetY(sprAlien->GetY() + distance);

		if ( screen.KeyPressed(GLFW_KEY_SPACE))
		{				
			jump = true;
			vel = 15;			
		}
			
		if (jump)
		{						
			vel-= grav * screen.ElapsedTime();

			if (vel <= 0)
			{	jump = false;			
				vel = 0;				
			}
		}					

		scene->Update(screen.ElapsedTime());
		scene->Render();		
					
		screen.Refresh();
	}
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
