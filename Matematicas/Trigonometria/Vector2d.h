class Vector2D
{
	public:
		float x;
		float y;
	
		Vector2D();
		Vector2D(const float x, const float y);

		static Vector2D fromPolar(const float a, const float r);
		Vector2D operator+(const Vector2D other) const;
		Vector2D operator-(const Vector2D other) const;
		Vector2D operator*(const float f) const;
		float Vector2D::Magnitude() const;
		Vector2D GetNormalized () const;
};