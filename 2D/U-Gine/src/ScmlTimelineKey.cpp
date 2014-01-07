#include "../include/ScmlTimelineKey.h"

ScmlTimelineKey ScmlTimelineKey::interpolate(ScmlTimelineKey nextKey,int nextKeyTime,float currentTime)
{
	return linear(nextKey, getTWithNextKey(nextKey,nextKeyTime,currentTime));
}

float ScmlTimelineKey::getTWithNextKey(ScmlTimelineKey nextKey,int nextKeyTime,float currentTime)
{
	if(curveType==INSTANT || time==nextKey.time)
		return 0;        
        
    float t = (currentTime - time) / (nextKey.time - time);

    switch (curveType)
	{
		case LINEAR:
			return t;
			break;

		case QUADRATIC:
			return(Quadratic(0.0,c1,1.0,t));
			break;

		case CUBIC:
			return(Cubic(0.0,c1,c2,1.0,t));
			break;

		default:
			return 0;
	}
}

ScmlTimelineKey ScmlTimelineKey::linear(ScmlTimelineKey keyB, float t)
{
	// overridden in inherited types  return linear(this,keyB,t);
	return ScmlTimelineKey();

}