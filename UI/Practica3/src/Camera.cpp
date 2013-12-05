#include "../include/Camera.h"
#include "../include/screen.h"
		
Camera::Camera()
{
	x = y = boundx0 = boundy0 = boundx1 = boundx1 = 0;
	followingSprite = NULL;
}

void Camera::SetPosition(double x, double y)
{
	SetX(x);
	SetY(y);
}

void Camera::SetX(double x)
{
	if (HasBounds())
	{	
		if (x <= GetMinX())
			this->x = GetMinX();
		else if (x >= GetMaxX())
			this->x = GetMaxX();
		else
			this->x = x;
	}
	else
		this->x = x;
}

void Camera::SetY(double y)
{
	if (HasBounds())
	{	
		if (y <= GetMinY())
			this->y = GetMinY();
		else if (y >= GetMaxY())
			this->y = GetMaxY();
		else
			this->y = y;
	}
	else
		this->y = y;
}

double Camera::GetX() const
{
	return x;
}

double Camera::GetY() const
{
	return y;
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1)
{
	boundx0 = bx0;
	boundy0 = by0;
	boundx1 = bx1;
	boundy1 = by1;

	SetPosition(GetX(),GetY());
}

bool Camera::HasBounds() const
{

	if (boundx0 == boundx1 )
		return false;
	else
		return true;
}

double Camera::GetMinX() const
{
	return boundx0;
}

double Camera::GetMinY() const
{
	return boundy0;
}

double Camera::GetMaxX() const
{
	return boundx1 - Screen::Instance().GetWidth();
}

double Camera::GetMaxY() const
{
	return boundy1 - Screen::Instance().GetHeight();
}

void Camera::FollowSprite(Sprite* sprite)
{
	followingSprite = sprite;
}

void Camera::Update()
{
	if (followingSprite)
	{
		SetX(followingSprite->GetScreenX() - (Screen::Instance().GetWidth() / 2));
		SetY(followingSprite->GetScreenY() - (Screen::Instance().GetHeight() / 2));
		
	}
}