#ifndef overhauserHPP
#define overhauserHPP

#include "Vector2d.h"
#include <vector>

class CRSpline
{
public:

    // Constructors and destructor
    CRSpline();
    CRSpline(const CRSpline&);
    ~CRSpline();

    // Operations
    void AddSplinePoint(const Vector2D& vector);
	Vector2D GetInterpolatedSplinePoint(float t);   // t = 0...1; 0=vp[0] ... 1=vp[max]
	int GetNumPoints();
	Vector2D& GetNthPoint(int n);

    // Static method for computing the Catmull-Rom parametric equation
    // given a time (t) and a vector quadruple (p1,p2,p3,p4).
    static Vector2D CatmullRollEq(float t, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4);

private:
    std::vector<Vector2D> m_vPoints;
    float delta_t;
};

#endif
