#include "Label.h"

bool Label::init( const std::string name, const Vector2& position,  const std::string font, const std::string text, unsigned char r, unsigned char g, unsigned char b, bool acceptPush)
{
	m_name = name;
	m_position = position;	
	m_r = r;
	m_g = g;
	m_b = b;	
	m_text = text;
	m_font = ResourceManager::Instance().LoadFont(String(font.c_str()));
	m_pushed = false;
	m_acceptPush = acceptPush;

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
	
	if (!m_pushed && m_acceptPush)
		Renderer::Instance().SetColor(m_r, m_g, m_b, 255);
	else
		Renderer::Instance().SetColor(WrapValue (m_r - 50,255)  , WrapValue (m_g - 50,255), WrapValue (m_b - 50,255), 255);

	m_font->Render(text,pos.x, pos.y);
	Renderer::Instance().SetColor(255, 255, 255, 255);
}

void Label::onInputEvent( const Message& message )
{
	switch( message.type )
	{
		case mtPointerButtonDown:
			m_pushed = true;			
			break;

		case mtPointerButtonUp:
			if( m_pushed )
				NOTIFY_LISTENERS( onClick( this ) );
			m_pushed = false;			
			break;
	}
}

void Label::destroy()
{

}

void Label::update()
{	
	if (!m_pointerIsOver && m_acceptPush)
		m_pushed = false;
}