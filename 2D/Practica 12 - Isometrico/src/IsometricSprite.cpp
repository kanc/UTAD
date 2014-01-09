#include "../include/IsometricSprite.h"
#include "../include/math.h"
#include <math.h>

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

void IsometricSprite::Update(double elapsed, const Map* map)
{
	Sprite::Update(elapsed, map);
	TransformIsoCoords(GetX(), GetY(), GetZ(), &screenX, &screenY);
}

void IsometricSprite::UpdateCollisionBox()
{

	double x = GetX() - GetImage()->GetHandleX() * fabs(GetScaleX());
	double y = GetY() - GetImage()->GetHandleX() * fabs(GetScaleX());
	double width = GetImage()->GetWidth() * fabs(GetScaleX());

	Sprite::UpdateCollisionBox(x, y, width, width);

}