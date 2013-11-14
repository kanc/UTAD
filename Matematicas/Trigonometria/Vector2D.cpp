#include "Vector2d.h"
#include <cmath>

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(const float fx, const float fy)
{
	x = fx;
	y = fy;
}

Vector2D Vector2D::fromPolar(const float a, const float r)
{
	return Vector2D(r * cos(a), r * sin(a));
}

Vector2D Vector2D::operator+(const Vector2D other) const
{
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D other) const
{
	return Vector2D(x - other.x, y - other.y);
}

//esto solo sirve para multiplicar Vector2d por un escalar pero no para un escalar por un Vector2d
Vector2D Vector2D::operator*(const float f) const
{
	return Vector2D(x * f, y * f);
}

float Vector2D::Magnitude() const
{
	return sqrt (x * x + y * y);
}

Vector2D Vector2D::GetNormalized() const
{
	float m = Magnitude();

	if (m > 0 )
		return Vector2D( x / m, y / m);
	else
		return Vector2D();

}