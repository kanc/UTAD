#include "../include/font.h"
#include "../include/screen.h"
#include "../include/renderer.h"

extern "C"  unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

Font::Font(String &filename) : Image(filename,16,16)
{	
	this->SetHandle(0,0);
	/*int x,y,comp;
	unsigned char *buffer = stbi_load(filename.ToCString(), &x, &y,&comp,4);*/

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