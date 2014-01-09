#include "../include/IsometricScene.h"
#include "../include/sprite.h"

IsometricScene::IsometricScene(IsometricMap* map, Image* imageBack, Image* imageFront) : MapScene((Map*) map, imageBack , imageFront)
{
	map->GenerateLayerSprites(this);
}

IsometricSprite* IsometricScene::CreateSprite(Image* image, Layer layer) 
{
	return (IsometricSprite *) Scene::CreateSprite(image, layer);
}

void IsometricScene::Update(double elapsed, Map* map)
{
	Scene::Update(elapsed,map);

	//ordenar los sprites de todas las capas de la scena
	for (uint8 i = 0; i < LAYER_COUNT; i++)	
		GetSprites((Scene::Layer)i).Sort(&CompareSprites);		
			
}


bool IsometricScene::CompareSprites(Sprite*& first, Sprite*& second)
{
	if (first->GetScreenY() < second->GetScreenY())
		return true;
	else
		return false;
}