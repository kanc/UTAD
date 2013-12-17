#include "Button.h"
#include "GUIManager.h"
#include <iostream>
#include <sstream>
#include "../include/Renderer.h"
#include "../include/Image.h"


//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Button::Button()
{
	m_pushed = false;
	m_font = NULL;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Button::init( const std::string name, const Vector2& position, const std::string& normalImage, const std::string& pushImage, const std::string& disabledImg)
{
	m_name				= name;
	m_position			= position;
	m_normalImage		= ResourceManager::Instance().LoadImage ( normalImage.c_str() );
	m_pushImage			= ResourceManager::Instance().LoadImage ( pushImage.c_str() );
	m_disabledImage		= ResourceManager::Instance().LoadImage ( disabledImg.c_str() );
	m_size				= Vector2( (float)m_normalImage->GetWidth(), (float)m_normalImage->GetHeight() );		

	return true;
}

void Button::addText(const std::string font, const std::string text, const unsigned char r, const unsigned char g, const unsigned char b)
{
	m_text = text;
	m_font = ResourceManager::Instance().LoadFont( font.c_str() );
	m_textR = r;
	m_textG = g;
	m_textB = b;		
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::update()
{
	if( !m_pointerIsOver )
		m_pushed = false;

}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::render()
{
	if( m_visible )
	{								
		Vector2 pos = getAbsolutePosition();

		Renderer::Instance().SetBlendMode( Renderer::ALPHA );

		if( m_pushed )
			Renderer::Instance().DrawImage( m_pushImage, pos.x, pos.y );
		else if( !m_pushed )
			Renderer::Instance().DrawImage( m_normalImage, pos.x, pos.y );
		else if (!isEnabled())								
			Renderer::Instance().DrawImage( m_disabledImage, pos.x, pos.y );
				
		renderButtonText(pos);	
	}
}

void Button::renderButtonText(Vector2 pos)
{
	if (m_font)
	{	
		float posx = pos.x + (m_size.x / 2) - (m_font->GetTextWidth(String(m_text.c_str())) / 2);
		float posy = pos.y +(m_size.y / 2) - (m_font->GetTextHeight(String(m_text.c_str())) / 2);
		Vector2 posText = Vector2(posx,posy);

		if (m_pushed || !isEnabled())
			Renderer::Instance().SetColor(WrapValue(-m_textR, 255), WrapValue(-m_textG, 255), WrapValue(-m_textB,  255), 255);
		else
			Renderer::Instance().SetColor(m_textR, m_textG, m_textB, 255);
		
		m_font->Render(m_text.c_str(), posText.x, posText.y);
		Renderer::Instance().SetColor(255,255,255,255);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::onInputEvent( const Message& message )
{
	switch( message.type )
	{
		case mtPointerButtonDown:
			if (isEnabled())
				m_pushed = true;
		break;

		case mtPointerButtonUp:
			if( m_pushed )
				NOTIFY_LISTENERS( onClick( this ) );

			m_pushed = false;
		break;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::destroy()
{
	if( m_normalImage )
	{
		delete m_normalImage;
		m_normalImage = NULL;
	}

	if( m_pushImage )
	{
		delete m_pushImage;
		m_pushImage = NULL;
	}

}