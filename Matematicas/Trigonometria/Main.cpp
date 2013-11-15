#define  _USE_MATH_DEFINES

#include "g4c_simple.h"
#include "Vector2d.h"
#include <cmath>

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

void main()
{

	MyDrawCircle(Vector2D(200,200),40);
	

}
