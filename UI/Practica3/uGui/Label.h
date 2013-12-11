#ifndef _LABEL_H_
#define _LABEL_H_

#include "Control.h"
#include "../include/font.h"
#include "../include/string.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/math.h"

class Label : public Control
{
	public:
		bool init( const std::string name, const Vector2& position,  const std::string font, const std::string text, unsigned char r, unsigned char g, unsigned char b, bool acceptPush);

		virtual void update();
		virtual void render();
		virtual void onInputEvent( const Message& message );
		virtual void destroy();	

		unsigned char GetR() { return m_r; }
		unsigned char GetG() { return m_g; }
		unsigned char GetB() { return m_b; }
		void SetColor(unsigned char r, unsigned char g, unsigned char b) { m_r = r; m_g = g; m_b = b; }

	private:
		Font* m_font;
		std::string m_text;
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;		
		bool m_acceptPush;

	protected:
		bool m_pushed;		

};

#endif