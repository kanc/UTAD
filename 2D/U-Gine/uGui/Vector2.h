#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h> 

struct Vector2
{
	Vector2(){}
	Vector2( float _x, float _y ) { x = _x; y = _y; }

	const Vector2 operator +(const Vector2 &v) const
	{	
		return Vector2(x+v.x, y+v.y);	
	}

	const Vector2 operator -(const Vector2 &v) const
	{	
		return Vector2(x-v.x, y-v.y);	
	}

	bool operator==(const Vector2 &v)
	{	
		return (x==v.x && y==v.y);
	}

	bool operator!=(const Vector2 &v)
	{	
		return (x!=v.x || y!=v.y);
	}

	const Vector2& operator=(const Vector2 &v)
	{	
		x= v.x; y= v.y;			
		return *this;
	}


	float x;
	float y;
};



#endif // _VECTOR2_H_