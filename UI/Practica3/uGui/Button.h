#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Control.h"
#include "ButtonLabel.h"

class Image;

class Button : public Control
{
public:
	Button();

	bool init( const std::string name, const Vector2& position, const std::string& normalImage, const std::string& pushImage );

	virtual void update();
	virtual void render();
	virtual void onInputEvent( const Message& message );
	virtual void destroy();
	void addLabel(const std::string font, const std::string text, const unsigned char r, const unsigned char g, const unsigned char b);

protected:
	Image*								m_normalImage;
	Image*								m_pushImage;
	bool								m_pushed;
	ButtonLabel*								m_label;
};


#endif // _BUTTON_H_