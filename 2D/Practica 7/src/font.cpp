#include "../include/font.h"
#include "../include/screen.h"
#include "../include/renderer.h"
#include "../include/glinclude.h"

extern "C"  unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

struct pixel
{
	unsigned char r,g,b,a;
	float x,y;

	pixel () { r = 0; g = 0; b = 0; a = 0; x = 0; y = 0; }
};

Font::Font(const String &filename) : Image(filename,16,16)
{		
	int imgWidth,imgHeight,comp;
	int frameSize = 0;
	unsigned char *buffer = stbi_load(filename.ToCString(), &imgWidth, &imgHeight,&comp,4);	

	for (int j = 0; j < imgHeight; j++) //recorremos las lineas verticales
	{	for (int i = 0; i < imgWidth; i++) //recorremos las lineas horizontales 
		{
			pixel actualPix; //cogemos informacion del pixel
			
			actualPix.r = buffer[(j * imgWidth * 4) + (i * 4)];
			actualPix.g = buffer[(j * imgWidth * 4) + (i * 4) + 1];
			actualPix.b = buffer[(j * imgWidth * 4) + (i * 4) + 2];
			actualPix.a = buffer[(j * imgWidth * 4) + (i * 4) + 3];						

			if ( actualPix.r == 255 && actualPix.g == 255 && actualPix.b == 0) //pixel amarillo
			{
				actualPix.x = i;
				actualPix.y = j;
				
				buffer[(j * imgWidth * 4) + (i * 4)] = 0;
				buffer[(j * imgWidth * 4) + (i * 4) + 1] = 0;
				buffer[(j * imgWidth * 4) + (i * 4) + 2] = 0;
				buffer[(j * imgWidth * 4) + (i * 4) + 3] = 0;
				
				pixel redPixel = SearchRedPixel(actualPix.x,actualPix.y,actualPix.x + this->GetWidth(),actualPix.y + this->GetHeight(),imgWidth,buffer);
				
				Glyph glyph = Glyph(frameSize,actualPix.y, this->GetWidth() - ( redPixel.x - actualPix.x ), redPixel.y);
				aGlyphs.Add(glyph);

				if (aGlyphs.Size() == 72 || aGlyphs.Size() == 111 || aGlyphs.Size() == 108 || aGlyphs.Size() == 97)
				{
					printf("");
				}



								
			}
			else if (actualPix.r == 0 && actualPix.g == 0 && actualPix.b == 0)			
				buffer[(j * imgWidth * 4) + (i * 4) + 3] = 0;			

			frameSize++;

			if (frameSize == this->GetWidth())
				frameSize = 0;
			
		}
	}
	
	glBindTexture(GL_TEXTURE_2D,this->GetTexId());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth,imgHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
}

pixel Font::SearchRedPixel(uint16 x1, uint16 y1, uint16 x2, uint16 y2, int imageWidth, unsigned char *buffer) const
{
	pixel actualPix;

	for (unsigned int j = y1; j <= y2; j++) 
	{	for (unsigned int i = x1; i <= x2; i++)
		{			
			actualPix.r = buffer[(j * imageWidth * 4) + (i * 4)];
			actualPix.g = buffer[(j * imageWidth * 4) + (i * 4) + 1];
			actualPix.b = buffer[(j * imageWidth * 4) + (i * 4) + 2];
			actualPix.a = buffer[(j * imageWidth * 4) + (i * 4) + 3];

			if ( actualPix.r == 255 && actualPix.g == 0 && actualPix.b == 0) //pixel rojo
			{
				actualPix.x = i;
				actualPix.y = j;
				buffer[(j * imageWidth * 4) + (i * 4) + 3] = 0; //ponemos el alpha a 0

				return actualPix;
			}
		}
	}

	return actualPix;
}

uint16 Font::GetSize() const
{
	return this->GetHeight();
}

uint16 Font::GetTextWidth(String &text) const
{	
	return text.Length() * this->GetWidth();
}

uint16 Font::GetTextHeight(String &text) const
{
	return this->GetHeight();
}
		
void Font::Render(const String& text, double x, double y)
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();
	double x2 = x;

	render.SetBlendMode(Renderer::ALPHA);

	for (int i = 0; i < text.Length(); i++)
	{		
		int charac = text[i];
		render.DrawImage(this,x2,y,charac);
		x2+=aGlyphs[charac].GetEndX() - aGlyphs[charac].GetBeginX();

	}
	
}