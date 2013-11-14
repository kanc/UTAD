#include "Matrix2D.h"
#include <cmath>

Matrix2D::Matrix2D()
{
	m_matrix[0] = new Vector2D(0,0);
	m_matrix[1] = new Vector2D(0,0);
}

Matrix2D::Matrix2D(Vector2D vcol1, Vector2D vcol2)
{	
	*m_matrix[0]=vcol1;
	*m_matrix[1]=vcol2;
}

Matrix2D::Matrix2D(float e11, float e12, float e21, float e22)
{
	m_matrix[0] = new Vector2D(e11,e21);
	m_matrix[1] = new Vector2D(e12,e22);
}

Matrix2D::~Matrix2D()
{
	delete m_matrix[0];
	delete m_matrix[1];
}

Matrix2D Matrix2D::GetRotationMatrix(float RadianAngle)
{
	Matrix2D rMatrix = Matrix2D (cosf(RadianAngle), sinf(RadianAngle) * -1.f, sinf(RadianAngle), cosf(RadianAngle));

	return rMatrix;
}

Matrix2D Matrix2D::GetScaleMatix(float factor)
{
	Matrix2D rMatrix= Matrix2D (factor, 0, 0, factor);

	return rMatrix;

}

Vector2D Matrix2D::operator*(const Vector2D &vector) const
{		
	//multiplicamos primer elemento de la primera fila con la x del vector y le sumamos la multiplicacion del segundo por la y
	float vx = m_matrix[0]->x * vector.x + m_matrix[1]->x * vector.y;
	//multiplicamos primer elemento de la segunda fila con la x del vector y le sumamos la multiplicacion del segundo por la y
	float vy = m_matrix[0]->y * vector.x + m_matrix[1]->y * vector.y;

	return Vector2D(vx,vy);
}

float Matrix2D::operator[](const int elem) const
{
	float content = 0;

	switch (elem)
	{
		case 0:	content = m_matrix[0]->x;	break;
		case 1:	content = m_matrix[1]->x;	break;
		case 2:	content = m_matrix[0]->y;	break;
		case 3:	content = m_matrix[1]->y;	break;
	}

	return content;
}