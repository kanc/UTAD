#ifndef VECTOR2D_H
#define VECTOR2D_H

class Matrix2D;

class Vector2D
{
	public:
		float x;
		float y;
	
		Vector2D();
		Vector2D(const float x, const float y);

		static Vector2D FromPolar(const float a, const float r);

		Vector2D operator+(const Vector2D &other) const;
		Vector2D operator-(const Vector2D &other) const;
		Vector2D operator*(const float f) const;
		float operator*(const Vector2D &other) const;
		Vector2D operator/(const float f) const;
		Vector2D operator*(const Matrix2D &matrix) const;
		void operator=(const Vector2D &other);
		bool operator==(const Vector2D &other) const;
		bool operator!=(const Vector2D &other) const;

		float Magnitude() const;
		float SquaredMagnitude() const;
		Vector2D GetNormalized() const;
		void Normalize();
		Vector2D GetRotated(float RadianAngle) const;
		void Rotate(float RadianAngle);
		void Draw(int color);
		float AngleWith(const Vector2D &other) const;
};

#endif