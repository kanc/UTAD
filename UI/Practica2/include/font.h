#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "image.h"
#include "string.h"

class Font : public Image
{
	public:
		Font (String &filename);

		virtual uint16 GetSize() const;
		virtual uint16 GetTextWidth(String &text) const;
		virtual uint16 GetTextHeight(String &text) const;
		
		virtual void Render(const String& text, double x, double y);

};

#endif