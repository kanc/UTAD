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

void ParallaxScene::Update(double elapsed, Map* map) {

    Scene::Update(elapsed, map);

	backX += autoBackSpeedX * elapsed;
	backY += autoBackSpeedY * elapsed;

	frontX += autoFrontSpeedX * elapsed;
	frontY += autoFrontSpeedY * elapsed;

}

void ParallaxScene::RenderBackground() const {

	Scene::RenderBackground();

	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().SetColor(255,255,255,255);

	if (backLayer)
		Renderer::Instance().DrawTiledImage(backLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), -backX + relBackSpeedX * GetCamera().GetX(), -backY + relBackSpeedY * GetCamera().GetY());

    if (frontLayer) 
		Renderer::Instance().DrawTiledImage(frontLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), -frontX + relFrontSpeedX * GetCamera().GetX(), -frontY + relFrontSpeedY * GetCamera().GetY());
}