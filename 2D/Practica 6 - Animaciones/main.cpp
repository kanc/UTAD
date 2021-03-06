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
<<<<<<< HEAD
	Image* alien =  ResourceManager::Instance().LoadImage("data/alienanim.png",8);	
=======
<<<<<<< HEAD
	Image* alien =  ResourceManager::Instance().LoadImage("data/alienanim.png",8);	

	SkeletonSprite* skeleton = new SkeletonSprite("data/animation.xml");
	skeleton->SetFPS(32);
=======
	Image* alien =  ResourceManager::Instance().LoadImage("data/alienanim.png",8,1);	
>>>>>>> 77b2bc5ecb210bf27fa26dcd08384dab4d376806
	alien->SetMidHandle();
>>>>>>> 50bb8de0eec51a95f1fd5a26cc4315c9d922e492

	SkeletonSprite* skeleton = new SkeletonSprite("data/animation.xml");
	skeleton->SetFPS(32);		

	MapScene* scene = new MapScene(mymap,back,front);
	scene->SetAutoBackSpeed(-16,0);
	scene->SetRelativeBackSpeed(0.5,0);
	scene->SetAutoFrontSpeed(0,0);
	scene->SetRelativeFrontSpeed(0.8,0);	

	Sprite* sprAlien = scene->CreateSprite(alien);
	sprAlien->SetPosition(10,10);
	sprAlien->SetFPS(16);
<<<<<<< HEAD
	sprAlien->SetFrameRange(1,8);
	sprAlien->SetScale(3,3);
=======
<<<<<<< HEAD
	sprAlien->SetFrameRange(1,8);
	sprAlien->SetScale(3,3);
=======
>>>>>>> 77b2bc5ecb210bf27fa26dcd08384dab4d376806
	sprAlien->SetCurrentFrame(1);
	sprAlien->SetFrameRange(1,20);
>>>>>>> 50bb8de0eec51a95f1fd5a26cc4315c9d922e492
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

		skeleton->SetPosition( screen.GetMouseX(),screen.GetMouseY());

		if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_1))
<<<<<<< HEAD
			skeleton->SetScale(-1, 1);
=======
			skeleton->SetScale(skeleton->GetScaleX() * -1, 1);
>>>>>>> 77b2bc5ecb210bf27fa26dcd08384dab4d376806
		
		double destX = sprAlien->GetX();

        if ( screen.KeyPressed(GLFW_KEY_LEFT) ) 
			destX = sprAlien->GetX() - 10;            
        else if ( screen.KeyPressed(GLFW_KEY_RIGHT) ) 
			destX = sprAlien->GetX() + 10;

		sprAlien->MoveTo(destX, sprAlien->GetY() - vel + grav, 200, 512);
		float distance = mymap->GetGroundY(sprAlien->GetX(), sprAlien->GetY()) -  (sprAlien->GetY() + sprAlien->GetImage()->GetHeight());

		screen.SetTitle(String::FromFloat(distance));

		if ((-vel + grav) > 0 && distance < 17) sprAlien->SetY(sprAlien->GetY() - (sprAlien->GetImage()->GetHeight() / 1.5f) + distance);

<<<<<<< HEAD
		if ( screen.KeyPressed(GLFW_KEY_SPACE) && !jump)
		{				
			jump = true;
			vel = 19;			
=======
		if ( screen.KeyPressed(GLFW_KEY_SPACE))
<<<<<<< HEAD
		{	jump = true;
=======
		{				
			jump = true;
>>>>>>> 50bb8de0eec51a95f1fd5a26cc4315c9d922e492
			vel = 15;			
>>>>>>> 77b2bc5ecb210bf27fa26dcd08384dab4d376806
		}
			
		if (jump)
		{						
			vel-= grav * screen.ElapsedTime();

			if (vel <= 0)
<<<<<<< HEAD
			{	jump = false;				
=======
			{	jump = false;			
>>>>>>> 50bb8de0eec51a95f1fd5a26cc4315c9d922e492
				vel = 0;				
			}
<<<<<<< HEAD
		}						
=======
		}					
>>>>>>> 77b2bc5ecb210bf27fa26dcd08384dab4d376806
		skeleton->Update(screen.ElapsedTime());
		scene->Update(screen.ElapsedTime());
		scene->Render();		
		skeleton->Render();
					
		screen.Refresh();
	}
	ResourceManager::Instance().FreeResources();
		
	return 0;
}
