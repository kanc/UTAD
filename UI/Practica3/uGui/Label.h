#ifndef _LABEL_H_
#define _LABEL_H_

#include "Control.h"
#include "../include/font.h"
#include "../include/string.h"

class Label : public Control
{
	public:
		bool init( const std::string name, const Vector2& position,  const std::string font, const std::string text, unsigned char r, unsigned char g, unsigned char b);

		virtual void update();
		virtual void render();
		virtual void onInputEvent( const Message& message );
		virtual void destroy();	

};

#endif