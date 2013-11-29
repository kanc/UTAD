#include "../include/font.h"
#include "../include/screen.h"
#include "../include/renderer.h"
#include "../include/glinclude.h"

extern "C"  unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

struct pixel
{
	int r,g,b,a,x,y;

	pixel () { r = -1; g = -1; b = -1; a = -1; }
};

Font::Font(const String &filename) : Image(filename,16,16)
{		
	int imgWidth,imgHeight,comp;
	unsigned char *buffer = stbi_load(filename.ToCString(), &imgWidth, &imgHeight,&comp,4);
	pixel prevYellowPix;	

	for (int j = 0; j < imgHeight; j++) //recorremos las lineas verticales
	{	for (int i = 0; i < imgWidth; i++) //recorremos las lineas horizontales 
		{
			pixel actualPix; //cogemos informacion del pixel
			
			actualPix.r = buffer[(j * i * 4) + (i * 4)];
			actualPix.g = buffer[(j * i * 4) + (i * 4) + 1];
			actualPix.b = buffer[(j * i * 4) + (i * 4) + 2];
			actualPix.a = buffer[(j * i * 4) + (i * 4) + 3];

			if ( actualPix.r == 255 && actualPix.g == 255 && actualPix.b == 0) //pixel amarillo
			{
				actualPix.x = i;
				actualPix.y = j;
				buffer[(j * i * 4) + (i * 4) + 3] = 0; //ponemos el alpha a 0

				if (prevYellowPix.r != -1) //si tenemos un pixel amarillo anterior, buscamos el rojo entre esos dos pixeles
				{
					pixel redPixel = SearchRedPixel(prevYellowPix.x,prevYellowPix.y,actualPix.x,actualPix.y,buffer);
				}
				else
					prevYellowPix = actualPix;
			}
		}
	}
	
	glBindTexture(GL_TEXTURE_2D,this->GetTexId());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth,imgHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);

}

pixel Font::SearchRedPixel(uint16 x1, uint16 y1, uint16 x2, uint16 y2, unsigned char *buffer) const
{
	pixel actualPix;

	for (unsigned int j = y1; j <= y2; j++) 
	{	for (unsigned int i = x1; i <= x2; i++)
		{			
			actualPix.r = buffer[(j * i * 4) + (i * 4)];
			actualPix.g = buffer[(j * i * 4) + (i * 4) + 1];
			actualPix.b = buffer[(j * i * 4) + (i * 4) + 2];
			actualPix.a = buffer[(j * i * 4) + (i * 4) + 3];

			if ( actualPix.r == 255 && actualPix.g == 0 && actualPix.b == 0) //pixel rojo
			{
				actualPix.x = i;
				actualPix.y = j;
				actualPix.a = buffer[(j * i * 4) + (i * 4) + 3] = 0; //ponemos el alpha a 0

				break;
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

	render.SetBlendMode(Renderer::ALPHA);

	for (int i = 0; i < text.Length(); i++)
		render.DrawImage(this,x + (i * GetSize()),y,text[i]);
}