#include "../include/IsometricSprite.h"
#include "../include/math.h"

IsometricSprite::IsometricSprite(Image* image) : Sprite(image)
{
	screenX = 0;
	screenY = 0;
}

void IsometricSprite::SetCollision(CollisionMode mode)
{
	if (mode == Sprite::CollisionMode::COLLISION_PIXEL)
		Sprite::SetCollision(Sprite::CollisionMode::COLLISION_RECT);
	else
		Sprite::SetCollision(mode);
}

void IsometricSprite::Update(double elapsed, const Map* map = NULL)
{
	Sprite::Update(elapsed, map);
	TransformIsoCoords(GetX(), GetY(), GetZ(), &screenX, &screenY);
}

void UpdateCollisionBox()
{
	/*x=isox­‐imagexhandle*fabs(scalex)
		y=isoy­‐imagexhandle*fabs(scalex)
		w=imagewidth*fabs(scalex)
		h=imageheight*fabs(scalex)
		Sprite::UpdateCollisionBox(x,y,w,h)*/

}