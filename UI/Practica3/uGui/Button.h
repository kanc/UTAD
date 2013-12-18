#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Control.h"
#include "ButtonLabel.h"

class Image;

class Button : public Control
{
public:
	Button();

	bool init( const std::string name, const Vector2& position, const std::string& normalImage, const std::string& pushImage, const std::string& disableImg, const std::string& overImg);

	virtual void update();
	virtual void render();
	virtual void onInputEvent( const Message& message );
	virtual void destroy();
	void addText(const std::string font, const std::string text, const unsigned char r, const unsigned char g, const unsigned char b);

protected:
	Image*								m_normalImage;
	Image*								m_pushImage;
	Image*								m_overImage;
	Image*								m_disabledImage;
	Font*								m_font;
	bool								m_pushed;
	string								m_text;
	uint8								m_textR;
	uint8								m_textG;
	uint8								m_textB;

private:
	void renderButtonText(Vector2 pos);
	
};


#endif // _BUTTON_H_