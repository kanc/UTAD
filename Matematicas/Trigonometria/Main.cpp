#define  _USE_MATH_DEFINES

#include "g4c_simple.h"
#include "Vector2d.h"
#include "Matrix2D.h"
#include "VectorMatrixOperations.h"
#include <cmath>
#include <stdio.h>
#include "CRSpline.h"

void drawSpline(CRSpline *spline, float precision = 2000);
void createSpline(CRSpline *spline, int numPoints);
void MyDrawCircle(Vector2D pos, float r);

void main()
{
	CRSpline* spline = new CRSpline();

	createSpline(spline,20);
	drawSpline(spline,15000);

	delete spline;	
}

void createSpline(CRSpline *spline, int numPoints)
{
	#define frand(n) ((n)*((float)rand() / (float)RAND_MAX))

	int w = 800;
	int h = 600;

	if (spline)
	    delete spline;

	spline = new CRSpline();

<<<<<<< HEAD
	srand(time_t(120));
=======
	srand(time_t(150));
>>>>>>> 196d503d720744cc938568a0ae8a5754cf2e4bfa
    
	for (int i = 0; i < numPoints; i++) {
		Vector2D v(10 + i * (w/20), 20.0 + frand(h/2));
		spline->AddSplinePoint(v);
	}
}

void drawSpline(CRSpline *spline, float precision)
{
	if (!spline)
		return;

	//pintamos los puntos
	for (int i = 0; i < spline->GetNumPoints(); i++) 
	{
		Vector2D& rv = spline->GetNthPoint(i);		
		MyDrawCircle(Vector2D(rv.x,rv.y),2);
	}

	// pintamos la spline
	for (int i = 0; i < precision; i++) 
	{
		float t = (float)i / precision;
		float t2 = (float)(i + 1)/ precision;

		Vector2D rv = spline->GetInterpolatedSplinePoint(t);
		Vector2D rv2 = spline->GetInterpolatedSplinePoint(t2);

		draw_line((int)rv.x, (int)rv.y, (int)rv2.x, (int)rv2.y);
	}
}


void MyDrawCircle(Vector2D pos, float r)
{	
	int numIteraciones = 100;	

	for (float i = 0; i < numIteraciones; i++)
	{
		//vamos obtenido el angulo diviendo la circunferencia (2 * PI) entre el numero de iteracion que queremos
		float a0 = (float)M_PI * 2 * i / numIteraciones;
		float a1 = (float)M_PI * 2 * (i + 1) / (numIteraciones);
		
		//creamos un vector con coordenadas polares de magnitud el radio y el angulo que calculamos y le sumamos el vector de posicion inicial
		Vector2D v0 = Vector2D::FromPolar(a0,r) + Vector2D(pos.x + r * cosf(a0),  pos.y + r * sinf(a0));
		Vector2D v1 = Vector2D::FromPolar(a1,r) + Vector2D(pos.x + r * cosf(a1),  pos.y + r * sinf(a1));
				
		//pintamos la linea del vector v0 al v1
		draw_line((int)v0.x, (int)v0.y, (int)v1.x, (int)v1.y, 8);
	}

}