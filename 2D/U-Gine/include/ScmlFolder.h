#ifndef UGINE_SCMLFOLDER_H
#define UGINE_SCMLFOLDER_H

#include "string.h"
#include "ScmlFile.h"

class ScmlFolder
{
	String name;
	ScmlFile files[];
};

#endif