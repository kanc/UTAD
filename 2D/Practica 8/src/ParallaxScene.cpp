#include "../include/ParallaxScene.h"

ParallaxScene::ParallaxScene(Image* imageBack, Image* imageFront )
{
	backLayer = imageBack;
	frontLayer = imageFront;

	backX = backY = frontX = frontY = 0;
}

const Image* ParallaxScene::GetBackLayer() const
{
	return backLayer;
}

const Image* ParallaxScene::GetFrontLayer() const
{
	return frontLayer;
}

void ParallaxScene::SetRelativeBackSpeed(double x, double y)
{
	relBackSpeedX = x;
	relBackSpeedY = y;
}

void ParallaxScene::SetRelativeFrontSpeed(double x, double y)
{
	relFrontSpeedX = x;
	relFrontSpeedY = y;
}

void ParallaxScene::SetAutoBackSpeed(double x, double y)
{
	autoBackSpeedX = x;
	autoBackSpeedY = y;
}

void ParallaxScene::SetAutoFrontSpeed(double x, double y)
{
	autoFrontSpeedX = x;
	autoFrontSpeedY = y;
}
void ParallaxScene::Update(double elapsed, Map* map) 
{
	Scene::Update(elapsed, map);
	
	backX -= autoBackSpeedX * elapsed;
	backX -= relBackSpeedX * GetCamera().GetX() * elapsed;

	backY -=  autoBackSpeedY * elapsed;		
	backY += relBackSpeedY * GetCamera().GetY() * elapsed;

	frontX -= autoFrontSpeedX * elapsed;
	frontY -= autoFrontSpeedY *elapsed;

	frontX -= relBackSpeedX * GetCamera().GetX() * elapsed;
	frontY += relBackSpeedY * GetCamera().GetY() * elapsed;

}

void ParallaxScene::RenderBackground() const
{
	Renderer::Instance().SetBlendMode( Renderer::ALPHA);
	Renderer::Instance().DrawTiledImage(backLayer,0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(),backX,backY);
	
	if (frontLayer)
		Renderer::Instance().DrawTiledImage(frontLayer,0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(),frontX,frontY);
}