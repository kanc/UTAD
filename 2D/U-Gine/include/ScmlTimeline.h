#ifndef UGINE_SCMLTIMELINE_H
#define UGINE_SCMLTIMELINE_H

#include "string.h"
#include "array.h"
#include "ScmlTimelineKey.h"

class ScmlTimeline
{
	public:
		ScmlTimeline() {}
		ScmlTimeline(String pname, eScmlObjectType oType) : name(pname), objectType(oType) {}

		String getName() { return name; }
		eScmlObjectType getObjectType() { return objectType; }
		Array <ScmlTimelineKey> getKeys() { return keys; }

	private:
		String name;
		eScmlObjectType objectType; 
		Array<ScmlTimelineKey> keys;
};

#endif