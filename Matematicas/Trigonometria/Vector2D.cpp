#include "Vector2d.h"
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

Vector2D Vector2D::operator/(const float scalar) const
{
	float f = 1.0f / scalar;

	return Vector2D(x * f, y * f);
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

//esto solo sirve para multiplicar Vector2d por un escalar pero no para un escalar por un Vector2d
Vector2D Vector2D::operator*(const float scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator*(const Matrix2D &matrix) const
{		
	//multiplicamos primer elemento de la primera fila con la x del vector y le sumamos la multiplicacion del segundo por la y
	float vx = matrix[0] * x + matrix[1] * y;
	//multiplicamos primer elemento de la segunda fila con la x del vector y le sumamos la multiplicacion del segundo por la y
	float vy = matrix[2] * x + matrix[2] * y;

	return Vector2D(vx,vy);
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
	float nx,ny;

	nx = (x * cosf(radianAngle)) - (y * sinf(radianAngle));
	ny = (y * cosf(radianAngle)) + (x * sinf(radianAngle));

	return Vector2D(nx,ny);
}

void Vector2D::Draw(int color)
{
	draw_line(0, 0, (int)x, (int)y, 8);
}

float Vector2D::AngleWith(const Vector2D &other) const
{
	float delta = 0;
	float m = Magnitude();
	float mother = other.Magnitude();

	//desarrollamos la ecuacion A · B = |A| * |B| * cos (angulo) ---> angulo = acos( A · B / |A| * |B| )
	if ((m != 0) && (mother != 0))
		delta = acosf( (*this * other) / (Magnitude() * other.Magnitude() ));

	return delta;
}