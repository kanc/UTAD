#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "image.h"
#include "string.h"
#include "glyph.h"
#include "array.h"

struct pixel;

class Font : public Image
{
	public:
		Font (const String &filename);

		virtual uint16 GetSize() const;
		virtual uint16 GetTextWidth(String &text);
		virtual uint16 GetTextHeight(String &text);
		virtual bool IsGlyphFont() const;
		
		virtual void Render(const String& text, double x, double y);

	private:
		pixel SearchRedPixel(uint16 x1, uint16 y1, uint16 x2, uint16 y2, int imgWidth, unsigned char *buffer) const;
		void LoadGlyphs(const String &filename);

		Array<Glyph> _aGlyphs;

};

#endif