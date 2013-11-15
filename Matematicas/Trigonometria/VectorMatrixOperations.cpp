#include "VectorMatrixOperations.h"

Vector2D operator*(const Vector2D &vector, const float scalar)
{
	return Vector2D(vector.x * scalar, vector.y * scalar);
}

Vector2D operator*(const float scalar, const Vector2D &vector)
{
	return Vector2D(vector.x * scalar, vector.y * scalar);
}

Vector2D operator/(const Vector2D &vector, const float scalar)
{
	float f = 1.0f / scalar;

	return Vector2D(vector.x * scalar, vector.y * scalar);
}

Vector2D operator/(const float scalar, const Vector2D &vector)
{
	float f = 1.0f / scalar;

	return Vector2D(vector.x * scalar, vector.y * scalar);
}

Vector2D operator*(const Matrix2D &matrix, const Vector2D &vector)
{	
	float vx = matrix[0] * vector.x + matrix[1] * vector.y;	
	float vy = matrix[2] * vector.x + matrix[2] * vector.y;

	return Vector2D(vx,vy);	
}

Vector2D operator*(const Vector2D &vector, const Matrix2D &matrix)
{			
	float g=matrix[0];

	double g2 = double(g * vector.x);

	double vx = (vector.x * matrix[0]) + (vector.x * matrix[2]);
	double vy = (vector.y * matrix[1]) + (vector.y * matrix[3]);

	return Vector2D(vx,vy);	
}