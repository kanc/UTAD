#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);

	IsometricMap* map = ResourceManager::Instance().LoadIsometricMap("data/isometric.tmx",3);	
	IsometricScene* scene = new IsometricScene(map);

	Image* imgcharac = ResourceManager::Instance().LoadImage("data/isoplayer.png",8,8);
	imgcharac->SetHandle(imgcharac->GetWidth()/2, imgcharac->GetHeight());

	IsometricSprite* charac = scene->CreateSprite(imgcharac);	
	charac->SetPosition(map->GetTileWidth() * 1.5, map->GetTileHeight() * 1.5);
	charac->SetCollision(Sprite::COLLISION_RECT);
	charac->SetFPS(25);
	scene->GetCamera().FollowSprite(charac);

	while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) 
	{		
		if ( !charac->IsMoving() ) 
		{
			double destX = charac->GetX();
			double destY = charac->GetY();
			if (screen.KeyPressed(GLFW_KEY_LEFT)) 
			{ 
				destX -= map->GetTileWidth(); 
				charac->SetFrameRange(5,8);
				charac->SetCurrentFrame(5);
			}
			else if (screen.KeyPressed(GLFW_KEY_RIGHT)) 
			{ 
				destX += map->GetTileWidth(); 
				charac->SetFrameRange(5,8);
				charac->SetCurrentFrame(5);
			}
			else if (screen.KeyPressed(GLFW_KEY_UP)) 
			{ 
				destY -= map->GetTileHeight();
				charac->SetFrameRange(5,8);
				charac->SetCurrentFrame(5);
			}
			else if (screen.KeyPressed(GLFW_KEY_DOWN)) 
			{ 
				destY += map->GetTileHeight();
				charac->SetFrameRange(5,8);
				charac->SetCurrentFrame(5);
			}
			
			// Nos movemos si la tile de destino no est· bloqueada
            int32 tilex = destX / map->GetTileWidth();
            int32 tiley = destY / map->GetTileHeight();

            if ( map->GetTileId(tilex, tiley) < 3  &&  map->GetLayerId(tilex, tiley) < 3 )
				charac->MoveTo(destX, destY, 256, 256);

		}
        if ( charac->IsMoving() ) {
            charac->SetFPS(25);
		} else {
            charac->SetFPS(0);
            //player->SetCurrentFrame(player->GetCurrentFrame() - (player->GetCurrentFrame()%FRAME_WIDTH));
		}
		
		// Actualizamos escena
        scene->Update(screen.ElapsedTime());

		// Dibujamos
        scene->Render();
        screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
		
	return 0;
}
