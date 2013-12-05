#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Control.h"
#include "../include/Image.h"


class Window : public Control
{
public:
	Window();

	bool Window::init( const std::string name );
	bool init( const std::string name, const Vector2& position, const std::string& backgroungImage );

	void update();
	void render();
	void onInputEvent( const Message& message );
	void destroy();

protected:

	// SDL
	Image*								m_canvas;
};


#endif // _WINDOW_H_