#ifndef UGINE_SCMLANIMATION_H
#define UGINE_SCMLANIMATION_H

#include "types.h"
#include "ScmlTimelineKey.h"
#include "math.h"

class ScmlAnimation
{
	public:

		ScmlAnimation() { time = 0; curveType = LINEAR; c1 = 0; c2 = 0; }
		ScmlAnimation(int ptime, eScmlCurveType cType, float pc1, float pc2) : time(ptime), curveType(cType), c1(pc1), c2(pc2) {}

		ScmlTimelineKey interpolate(ScmlTimelineKey nextKey,int nextKeyTime,float currentTime);
		float getTWithNextKey(ScmlTimelineKey nextKey,int nextKeyTime,float currentTime);		

	private:
		int time;
		eScmlCurveType curveType;
		float c1, c2;
};

#endif