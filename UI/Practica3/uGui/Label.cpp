#include "Label.h"

bool Label::init( const std::string name, const Vector2& position,  const std::string font, const std::string text, unsigned char r, unsigned char g, unsigned char b)
{
	m_name = name;
	m_position = position;	
	m_r = r;
	m_g = g;
	m_b = b;	
	m_text = text;
	m_font = ResourceManager::Instance().LoadFont(String(font.c_str()));
	m_pushed = false;

	if (m_font)
	{
		m_size = Vector2(m_font->GetTextWidth(String (m_text.c_str())),m_font->GetTextHeight(String (m_text.c_str())));
		return true;
	}
	else
		return false;
}

void Label::render()
{
	Vector2 pos = getAbsolutePosition();
	String text = String(m_text.c_str());
	Renderer::Instance().SetColor(m_r, m_g, m_b, 255);
	m_font->Render(text,pos.x, pos.y);

}

void Label::onInputEvent( const Message& message )
{
	switch( message.type )
	{
		case mtPointerButtonUp:			
			NOTIFY_LISTENERS( onClick( this ) );
			break;
	}
}

void Label::destroy()
{
	delete m_font;
	m_font = NULL;
}

void Label::update()
{
}