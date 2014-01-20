#ifndef UGINE_ISOMETRICSCENE_H
#define UGINE_ISOMETRICSCENE_H

#include "MapScene.h"
#include "IsometricMap.h"
#include "IsometricSprite.h"

class IsometricScene : public MapScene
{
	public:
		IsometricScene() {}
		IsometricScene(IsometricMap* map, Image* imageBack = NULL, Image* imageFront = NULL);
		virtual IsometricSprite* CreateSprite(Image* image, Layer layer = LAYER_BACK);
		virtual void Update(double elapsed, Map* map = NULL);

	protected:
		static bool CompareSprites(Sprite*& first, Sprite*& second);
};

#endif