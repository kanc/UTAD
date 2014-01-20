#include "CollisionManager.h"
#include "screen.h"
#include "math.h"
#include <math.h>

CollisionManager* CollisionManager::manager = NULL;

 const CollisionManager& CollisionManager::Instance()
 {
	 if (!manager)
		 manager = new CollisionManager();

	 return *manager;	
 }

 //comprobamos que la distancia entre los centros de los dos circulos sea menos que la suma de sus radios
 bool CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const
{
	double distance = SquareDistance(x1,y1,x2,y2);	

	if (distance < (r1 + r2) * (r1 + r2))	
		return true;
	else
		return false;
}

 //recoremos el buffer de pixeles y comprobamos si los pixeles opacos estan a una distancia menos que el radio del circulo
 bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData* pixels, double px, double py) const
{
	for (int i = 0; i < pixels->GetWidth(); i++)
	{	for (int j = 0; j < pixels->GetHeight(); j++)
		{	if (pixels->GetData(i,j) && SquareDistance(cx, cy, i + px, j + py) < (cr * cr))
				return true;
		}
	}

	return false;
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const
{
	double closestX,closestY;
	
	//buscamos el punto mas cercano desde el centro hasta el rectangulo
	ClosestPointToRect(cx,cy,rx,ry,rw,rh,&closestX,&closestY);
	
	//si la distancia desde el centro al punto mas cercano es menor que el radio colisiona
	return SquareDistance(cx,cy,closestX, closestY) < (cr * cr);
}

//comprobamos si colisionan los rectangulos que contienen los pixeles, obtenemos la zona en la que se solapan y comprobamos en esa zona si hay un pixel para los dos sprites
bool CollisionManager::PixelsToPixels(const CollisionPixelData* p1, double x1, double y1, const CollisionPixelData* p2, double x2, double y2) const
{
	//si los dos rectangulos se solapan
	if (RectsOverlap(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight())) 
	{
		double rx, ry, rw, rh;
		
		//obtenemos el rectangulo de solapamiento
		OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &rx, &ry, &rw, &rh);

		//obtenemos los pixeles del los dos rectangulos donde empieza al rectangulo de solapamiento
		uint16 rect1x = uint16(rx - x1);
		uint16 rect1y = uint16(ry - y1);
		uint16 rect2x = uint16(rx - x2);
		uint16 rect2y = uint16(ry - y2);

		//recorremos desde esos puntos nuestro buffer de booleanos y si los dos son opacos, 
		for (int i = 0; i < rw; i++)
			for (int j = 0; j < rh; j++)
				if (p1->GetData(rect1x + i, rect1y + j)  &&  p2->GetData(rect2x + i, rect2y + j))
					return true;
	}

	return false;
}

//comprobamos si colisiona el rectangulo y el rectangulo que contiene los pixeles, obtenemos la zona en la que se solapan y comprobamos en esa zona si hay un pixel opaco en el buffer
bool CollisionManager::PixelsToRect(const CollisionPixelData* pixels, double px, double py, double rx, double ry, double rw, double rh) const
{	
	if (RectsOverlap(px,py, pixels->GetWidth(), pixels->GetHeight(),rx,ry,rw,rh))
	{
		double overlapx, overlapy, overlapw, overlaph;
		OverlappingRect(px,py,pixels->GetWidth(), pixels->GetHeight(),rx,ry,rw,rh,&overlapx,&overlapy,&overlapw, &overlaph);

		uint16 rect1x = uint16(overlapx - px);
		uint16 rect1y = uint16(overlapy - py);
		uint16 rect2x = uint16(overlapx - rx);
		uint16 rect2y = uint16(overlapy - ry);

		//recorremos desde esos puntos nuestro buffer de booleanos y si algun pixel es opaco colisionan
		for (int i = 0; i < overlapw; i++)
			for (int j = 0; j < overlaph; j++)
				if (pixels->GetData(rect1x + i, rect1y + j))
					return true;
	}

	return false;
}

bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const
{
	return RectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2);
}		