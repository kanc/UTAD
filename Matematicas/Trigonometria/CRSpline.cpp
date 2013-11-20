#include "CRSpline.h"
#include "VectorMatrixOperations.h"

CRSpline::CRSpline() : m_vPoints(), delta_t(0)
{
}

CRSpline::CRSpline(const CRSpline& spline)
{
    for (int i = 0; i < (int)spline.m_vPoints.size(); i++)
        m_vPoints.push_back(spline.m_vPoints[i]);

    delta_t = spline.delta_t;
}

CRSpline::~CRSpline()
{
}

// Solve the Catmull-Rom parametric equation for a given time(t) and vector quadruple (p1,p2,p3,p4)
Vector2D CRSpline::CatmullRollEq(float t, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4)
{
    float t2 = t * t;
    float t3 = t2 * t;

    float b1 = .5 * (  -t3 + 2*t2 - t);
    float b2 = .5 * ( 3*t3 - 5*t2 + 2);
    float b3 = .5 * (-3*t3 + 4*t2 + t);
    float b4 = .5 * (   t3 -   t2    );

    return (p1*b1 + p2*b2 + p3*b3 + p4*b4); 
}

void CRSpline::AddSplinePoint(const Vector2D& vector)
{
	m_vPoints.push_back(vector);

    delta_t = (float)1 / (float)m_vPoints.size();
}

Vector2D CRSpline::GetInterpolatedSplinePoint(float t)
{
    // Find out in which interval we are on the spline
    int p = (int)(t / delta_t);

    // Compute local control point indices
	
	#define BOUNDS(pp) { if (pp < 0) pp = 0; else if (pp >= (int)m_vPoints.size()-1) pp = m_vPoints.size() - 1; }

    int p0 = p - 1;     BOUNDS(p0);
    int p1 = p;         BOUNDS(p1);
    int p2 = p + 1;     BOUNDS(p2);
    int p3 = p + 2;     BOUNDS(p3);

    // Relative (local) time 
	float lt = (t - delta_t*(float)p) / delta_t;

	// Interpolate
    return CRSpline::CatmullRollEq(lt, m_vPoints[p0], m_vPoints[p1], m_vPoints[p2], m_vPoints[p3]);
}

int CRSpline::GetNumPoints()
{
	return m_vPoints.size();
}

Vector2D& CRSpline::GetNthPoint(int n)
{
	return m_vPoints[n];
}


