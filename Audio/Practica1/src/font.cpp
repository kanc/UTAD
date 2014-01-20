#include "../include/font.h"
#include "../include/screen.h"
#include "../include/renderer.h"
#include "../include/glinclude.h"

extern "C"  unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

struct pixel
{
	unsigned char r,g,b,a;
	uint16 x,y;

	pixel () { r = 0; g = 0; b = 0; a = 0; x = 0; y = 0; }
};


Font::Font(const String &filename) : Image(filename,16,16)
{		
	LoadGlyphs(filename);
}

void Font::LoadGlyphs(const String &filename)
{
	int imgWidth,imgHeight,comp;
	int frameSizeW, frameSizeH;
	unsigned char *buffer = stbi_load(filename.ToCString(), &imgWidth, &imgHeight,&comp,4);	

	frameSizeH = frameSizeW = 0;

	for (int j = 0; j < imgHeight; j++) //recorremos las lineas verticales
	{	
		frameSizeH++; //vamos calculando donde caeria el tamaño vertical "real" del frame para calcular la posicion relativa del glifo

		if (frameSizeH == this->GetHeight())
			frameSizeH = 0;

		for (int i = 0; i < imgWidth; i++) //recorremos las lineas horizontales 
		{
			frameSizeW++; //vamos calculando donde caeria el tamaño horizontal "real" del frame para calcular la posicion relativa del glifo

			if (frameSizeW == this->GetWidth())
				frameSizeW = 0;

			pixel actualPix; //cogemos informacion del pixel
			
			actualPix.r = buffer[(j * imgWidth * 4) + (i * 4)];
			actualPix.g = buffer[(j * imgWidth * 4) + (i * 4) + 1];
			actualPix.b = buffer[(j * imgWidth * 4) + (i * 4) + 2];
			actualPix.a = buffer[(j * imgWidth * 4) + (i * 4) + 3];						

			if ( actualPix.r == 255 && actualPix.g == 255 && actualPix.b == 0) //pixel amarillo
			{
				actualPix.x = i;
				actualPix.y = j;
				
				buffer[(j * imgWidth * 4) + (i * 4) + 3] = 0; //ponemos el pixel transparente
				
				//buscamos el pixel rojo, desde la posicion del pixel amarillo hasta el tamaño del frame tanto vertical como horizonalmente
				pixel redPixel = SearchRedPixel(actualPix.x,actualPix.y,actualPix.x + this->GetWidth(),actualPix.y + this->GetHeight(),imgWidth,buffer);
				
				Glyph glyph = Glyph(frameSizeW, frameSizeH, ( redPixel.x - actualPix.x ), (redPixel.y - actualPix.y));
				_aGlyphs.Add(glyph);
								
			} //los pixeles negros, tambien transparentes
			else if (actualPix.r == 0 && actualPix.g == 0 && actualPix.b == 0)			
				buffer[(j * imgWidth * 4) + (i * 4) + 3] = 0;						
		}
	}
	
	//cargamos el nuevo buffer con la textura modificada
	glBindTexture(GL_TEXTURE_2D,this->GetTexId());		
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth,imgHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
	
}

pixel Font::SearchRedPixel(uint16 x1, uint16 y1, uint16 x2, uint16 y2, int imageWidth, unsigned char *buffer) const
{
	pixel actualPix;

	for (uint16 j = y1; j <= y2; j++) 
	{	for (uint16 i = x1; i <= x2; i++)
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

void Font::Render(const String& text, double x, double y)
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();
	double x2 = x;

	render.SetBlendMode(Renderer::ALPHA);

	for (int i = 0; i < text.Length(); i++)
	{		
		unsigned char charac = text[i];
		
		if (IsGlyphFont())
		{	//en esta fuente el glifo comienza justo en el inicio del frame, pero pudiera ser que en otra estuviera centrado
			//asi que restamos la distancia desde el inicio del frame al inicio del glifo y sumamos uno para que no queden pegadas del todo
			x2 = x2 - _aGlyphs[charac].GetBeginX() + 1;

			render.DrawImage(this,x2,y,charac);

			x2+=_aGlyphs[charac].GetEndX() - _aGlyphs[charac].GetBeginX(); //avanzamos el tamaño del glifo
		}
		else
			render.DrawImage(this,x + (i * this->GetWidth()),y,charac);
	}
	
}

bool Font::IsGlyphFont() const
{
	return (_aGlyphs.Size() > 0 );
}

uint16 Font::GetSize() const
{
	return this->GetHeight();
}

uint16 Font::GetTextWidth(String &text)
{	
	if (!IsGlyphFont())
		return text.Length() * this->GetWidth();
	else
	{
		uint16 width = 0;

		for (int i = 0; i < text.Length(); i++)
		{	
			unsigned char charac = text[i];									
			width+= _aGlyphs[charac].GetEndX() - _aGlyphs[charac].GetBeginX();			
		}

		return width;
	}
}

uint16 Font::GetTextHeight(String &text) 
{
	if (!IsGlyphFont())
		return this->GetHeight();
	else
	{
		uint16 height = 0;

		for (int i = 0; i < text.Length(); i++)
		{	
			unsigned char charac = text[i];
			
			if (_aGlyphs[charac].GetEndY() - _aGlyphs[charac].GetBeginY() > height)
			{
				height = _aGlyphs[charac].GetEndY() - _aGlyphs[charac].GetBeginY();
			}				
		}

		return height;
	}
}
		
