#include "Vector2d.h"
#include "VectorMatrixOperations.h"
#include "Matrix2D.h"
#include "g4c_simple.h"
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

Vector2D Vector2D::FromPolar(const float a, const float r)
{
	return Vector2D(r * cosf(a), r * sinf(a));
}

bool Vector2D::operator==(const Vector2D &other) const
{
	return ( (x == other.x) && (y == other.y) );
}

bool Vector2D::operator!=(const Vector2D &other) const
{
	return ( (x != other.x) || (y != other.y) );
}

void Vector2D::operator=(const Vector2D &other)
{
	x = other.x;
	y = other.y;
}

Vector2D Vector2D::operator+(const Vector2D &other) const
{
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
	return Vector2D(x - other.x, y - other.y);
}

//devuelve el producto escalar de dos vectores, es la proyeccion de uno sobre otro, si es 0 son perpendiculares
float Vector2D::operator*(const Vector2D &other) const
{
	return (x * other.x + y * other.y);
}

//devuelve el modulo del vector al cuadrado (menos costoso que la raiz) 
float Vector2D::SquaredMagnitude() const
{
	return (x * x + y * y) * (x * x + y * y);
}

//devuelve el modulo del vector
float Vector2D::Magnitude() const
{
	return sqrt (x * x + y * y);
}

//devuelve un vector unitario de nuestro vector
Vector2D Vector2D::GetNormalized() const
{
	float m = Magnitude();

	if (m > 0 )
		return Vector2D( x / m, y / m);
	else
		return Vector2D();
}

//devuelve un vector unitario de nuestro vector
void Vector2D::Normalize()
{
	float m = Magnitude();

	if (m > 0 )
	{
		x = x / m;
		y = y / m;
	}	
}

//seria como aplicar la matriz de rotacion
void Vector2D::Rotate(float radianAngle)
{
	x = (x * cosf(radianAngle)) - (y * sinf(radianAngle));
	y = (y * cosf(radianAngle)) + (x * sinf(radianAngle));
	
}

Vector2D Vector2D::GetRotated(float radianAngle) const
{
	Matrix2D rotMatrix = Matrix2D::GetRotationMatrix(radianAngle);	

	return rotMatrix * *this;
}

void Vector2D::Draw(int color)
{
	draw_line(0, 0, (int)x, (int)y, 8);
}

float Vector2D::AngleWith(const Vector2D &other) const
{
	float delta = 0;
	float mag = Magnitude();
	float magOther = other.Magnitude();

	//desarrollamos la ecuacion A · B = |A| * |B| * cos (angulo) ---> angulo = acos( A · B / |A| * |B| )
	if ((mag != 0) && (magOther != 0))
		delta = acosf( (*this * other) / (mag * magOther) );

	return delta;
}