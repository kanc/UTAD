#include "Matrix2D.h"
#include "VectorMatrixOperations.h"
#include <cmath>

Matrix2D::Matrix2D()
{
	m_matrix[0] = new Vector2D(0,0);
	m_matrix[1] = new Vector2D(0,0);
}

Matrix2D::Matrix2D(const Matrix2D &matrix)
{
	m_matrix[0] = new Vector2D(matrix[0],matrix[2]);
	m_matrix[1] = new Vector2D(matrix[1],matrix[3]);
}

Matrix2D::Matrix2D(Vector2D vcol1, Vector2D vcol2)
{	
	m_matrix[0]=new Vector2D();
	m_matrix[1]=new Vector2D();

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
	Matrix2D rMatrix(cosf(RadianAngle), sinf(RadianAngle) * -1.f, sinf(RadianAngle), cosf(RadianAngle));

	return rMatrix;
}

Matrix2D Matrix2D::GetScaleMatrix(float factor)
{
	Matrix2D rMatrix= Matrix2D (factor, 0, 0, factor);

	return rMatrix;
}

Matrix2D Matrix2D::operator*(const Matrix2D &other) const
{		
	float e11, e12, e21, e22;

	//suponiendo la primera matrix como A y la que se nos pasa como B:
	e11 = m_matrix[0]->x * other[0] + m_matrix[1]->x * other[2]; //A11 * B11 + A12 * B21
	e12 = m_matrix[0]->x * other[1] + m_matrix[1]->x * other[3]; //A11 * B12 + A12 * B22
	e21 = m_matrix[0]->y * other[0] + m_matrix[1]->y * other[2]; //A21 * B11 + A22 * B21
	e22 = m_matrix[0]->y * other[1] + m_matrix[1]->y * other[3]; //A21 * B12 + A22 * B22

	return Matrix2D(e11,e12,e21,e22);
}

Matrix2D Matrix2D::operator+(const Matrix2D &other) const
{		
	float e11, e12, e21, e22;
	
	e11 = m_matrix[0]->x + other[0]; 
	e12 = m_matrix[1]->x + other[1]; 
	e21 = m_matrix[0]->y + other[2]; 
	e22 = m_matrix[1]->y + other[3];

	return Matrix2D(e11,e12,e21,e22);
}

Matrix2D Matrix2D::operator-(const Matrix2D &other) const
{		
	float e11, e12, e21, e22;
	
	e11 = m_matrix[0]->x - other[0]; 
	e12 = m_matrix[1]->x - other[1]; 
	e21 = m_matrix[0]->y - other[2]; 
	e22 = m_matrix[1]->y - other[3];

	return Matrix2D(e11,e12,e21,e22);
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

Matrix2D Matrix2D::GetTransposed() const
{
	Matrix2D oTransMatrix (m_matrix[0]->x, m_matrix[0]->y, m_matrix[1]->x, m_matrix[1]->y);

	return oTransMatrix;
}

void Matrix2D::Transpose()
{
	float temp;
	
	temp = m_matrix[1]->x; //guardamos el elemento 12

	m_matrix[1]->x = m_matrix[0]->y; //metemos e21 en 12
	m_matrix[0]->y = temp; //metemos el 12 en el e21
}

Matrix2D Matrix2D::GetInverse() const
{
	float det = GetDeterminant();	
	
	if (det != 0)
	{		
		//invertimos el elemento e11 con el e22 y e12 y e21 con signo cambiado
		//y multiplicamos esa nueva matriz por 1 / determinante

		Matrix2D newmatrix(m_matrix[1]->y, m_matrix[1]->x * -1.0f, m_matrix[0]->y * -1.0f, m_matrix[0]->x);

		return newmatrix * (1 / det);
	}
	else
		return Matrix2D();
}

float Matrix2D::GetDeterminant() const
{
	return m_matrix[0]->x * m_matrix[1]->y - (m_matrix[1]->x * m_matrix[0]->y);
}

