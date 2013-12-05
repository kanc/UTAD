#ifndef _IEVENTLISTENER_H_
#define _IEVENTLISTENER_H_

#include "Message.h"

class Control;

class IEventListener
{
public:
	virtual void onClick( Control* sender ){};
	virtual void onGotFocus( Control* sender ){};
	virtual void onLostFocus( Control* sender ){};
	virtual void onKeyDown( Control* sender, int keyCode ){};
	virtual void onKeyUp( Control* sender, int keyCode ){};
};

#endif //_IEVENTLISTENER_H_