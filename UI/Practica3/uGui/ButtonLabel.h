#ifndef _BUTTONLABEL_H_
#define _BUTTONLABEL_H_

#include "Label.h"

class ButtonLabel : public Label
{
	public:
		virtual void onInputEvent( const Message& message, const bool fromButton = false );
};

#endif 