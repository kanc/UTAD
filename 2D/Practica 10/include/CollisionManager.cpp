#include "CollisionManager.h"
#include "math.h"

CollisionManager* CollisionManager::manager = NULL;



bool CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const
{
	double distancex = x2 - x1;
	double distancey = y2 - y1;

	if ((distancex + distancey) * (distancex + distancey) < (r1 + r2) * (r1 + r2))	
		return true;
	else
		return false;

}

bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData* pixels, double px, double py) const
{
	return false;
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const
{
	//si el centro del circulo estan dentro del rectangulo
	if (PointInRect(cx,cy,rx,ry,rw,rh))	
		return true;

	//o si alguno de los cuatro puntos del rectangulo esta dentro del circulo
	if (PointInCircle (rx,ry,cx,cy,cr))
		return true;

	if (PointInCircle (rx + rw,ry,cx,cy,cr))
		return true;

	if (PointInCircle (rx,ry + rh,cx,cy,cr))
		return true;

	if (PointInCircle (rx + rw,ry + rh,cx,cy,cr))
		return true;

	return false;

}

bool CollisionManager::PixelsToPixels(const CollisionPixelData* p1, double x1, double y1, const CollisionPixelData* p2, double x2, double y2) const
{
	return true;
}

bool CollisionManager::PixelsToRect(const CollisionPixelData* pixels, double px, double py, double rx, double ry, double rw, double rh) const
{
	return true;
}
bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const
{
	//comprobamos si alguno los cuatro puntos del primer rectangulo estan contenido dentro del segundo
	if (PointInRect(x1,y1,x2,y2,w2,h2))	
		return true;

	if (PointInRect(x1 + w1,y1,x2,y2,w2,h2))	
		return true;

	if (PointInRect(x1,y1 + h1,x2,y2,w2,h2))	
		return true;

	if (PointInRect(x1 + w1,y1 + h1,x2,y2,w2,h2))	
		return true;

	return false;

}		