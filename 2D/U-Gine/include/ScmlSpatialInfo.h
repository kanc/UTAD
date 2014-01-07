#ifndef UGINE_SCMLSPATIALINFO_H
#define UGINE_SCMLSPATIALINFO_H

#include "math.h"
#include <math.h>

class ScmlSpatialInfo
{
	public:
		ScmlSpatialInfo() { x = 0; y = 0; angle = 0; scaleX = 1; scaleY = 1; a = 1; spin = 1; }
		ScmlSpatialInfo(float px, float py, float pangle, float pscaleX, float pscaleY, float pa, int pspin) : x(px), y(py), angle(pangle), scaleX(pscaleX), scaleY(pscaleY), a(pa), spin(pspin) {}

		float getX() { return x; }
		void setX (float px) { x = px; }
		float getY() { return y; }
		void setY (float py) { y = py; }
		float getAngle() { return angle; }
		void setAngle (float pangle) { angle = pangle; }
		float getScaleX() {return scaleX; }
		void setScaleX (float sx) { scaleX = sx; }
		float getScaleY() {return scaleY; }
		void setScaleY (float sy) { scaleY = sy; }
		float getA() { return a; }
		void setA (float pa) { a = pa; }
		int getSpin() { return spin; }
		void setSpin (int pspin) { spin = pspin; }

		ScmlSpatialInfo* unmapFromParent(ScmlSpatialInfo* parentInfo)
		{
			ScmlSpatialInfo* unmappedObj = this;
			unmappedObj->setAngle(unmappedObj->getAngle() + parentInfo->getAngle());
			unmappedObj->setScaleX(unmappedObj->getScaleX() * parentInfo->getScaleX());
			unmappedObj->setScaleY(unmappedObj->getScaleY() * parentInfo->getScaleY());
			unmappedObj->setA(unmappedObj->getA() * parentInfo->getA());			
	
			if(x!=0 || y!=0)  
			{
				float preMultX = x * parentInfo->getScaleX();
				float preMultY = y * parentInfo->getScaleY();
				float s = sin(DegSin(parentInfo->getAngle()));
				float c = cos(DegSin(parentInfo->getAngle()));
				
				unmappedObj->setX((preMultX * c) - (preMultY * s));
				unmappedObj->setY((preMultX * s) - (preMultY * c));
				unmappedObj->setX(unmappedObj->getX() + parentInfo->getX());
				unmappedObj->setY(unmappedObj->getY() + parentInfo->getY());
			}
			else 
			{
				// Mandatory optimization for future features           
				unmappedObj->setX(parentInfo->getX());
				unmappedObj->setY(parentInfo->getY());				
			}

			return unmappedObj;
		}

	private:
		float x, y, angle, scaleX, scaleY, a;
	    int spin;

};

#endif