#ifndef VMOPERATIONS_H
#define VMOPERATIONS_H

#include "Vector2d.h"
#include "Matrix2D.h"

Vector2D operator*(const Vector2D &vector, const float f);
Vector2D operator*(const float f, const Vector2D &vector);

Vector2D operator/(const Vector2D &vector, const float f);
Vector2D operator/(const float f, const Vector2D &vector);

Vector2D operator*(const Vector2D &vector, const Matrix2D &matrix);
Vector2D operator*(const Matrix2D &matrix, const Vector2D &vector);

Matrix2D operator*(const float f, const Matrix2D &matrix);
Matrix2D operator*(const Matrix2D &matrix,const float f);

#endif