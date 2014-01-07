#ifndef UGINE_SCMLTIMELINEKEY_H
#define UGINE_SCMLTIMELINEKEY_H

#include "math.h"
#include <math.h>
#include "types.h"

class ScmlTimelineKey
{
	public:
		ScmlTimelineKey interpolate(ScmlTimelineKey nextKey,int nextKeyTime,float currentTime);
		float getTWithNextKey(ScmlTimelineKey nextKey,int nextKeyTime,float currentTime);

	private:
		ScmlTimelineKey ScmlTimelineKey::linear(ScmlTimelineKey keyB, float t);

		int time;
		eScmlCurveType curveType;
		float c1, c2;
};

#endif