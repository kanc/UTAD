#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "Vector2d.h"

class Matrix2D
{
	private:	
		Vector2D *m_matrix[2];

	public:
		Matrix2D();
		Matrix2D(Vector2D vcol1, Vector2D vcol2);
		Matrix2D(float e11, float e12, float e21, float e22);
		~Matrix2D();
		
		Vector2D operator*(const Vector2D &vector) const;
		float operator[](const int elem) const;

		static Matrix2D GetRotationMatrix(float RadianAngle);
		static Matrix2D GetScaleMatix(float factor);
};

#endif