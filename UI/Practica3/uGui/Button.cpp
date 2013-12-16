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
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Button::init( const std::string name, const Vector2& position, const std::string& normalImage, const std::string& pushImage )
{
	m_name				= name;
	m_position			= position;
	m_normalImage		= new Image( normalImage.c_str() );
	m_pushImage			= new Image( pushImage.c_str() );
	m_size				= Vector2( (float)m_normalImage->GetWidth(), (float)m_normalImage->GetHeight() );
	m_label				= NULL;

	return true;
}

void Button::addLabel(const std::string font, const std::string text, const unsigned char r, const unsigned char g, const unsigned char b)
{
	Font* fnt = ResourceManager::Instance().LoadFont( font.c_str() );
	float posx = (m_size.x / 2) - (fnt->GetTextWidth(String(text.c_str())) / 2);
	float posy = (m_size.y / 2) - (fnt->GetTextHeight(String(text.c_str())) / 2);
	Vector2 pos = Vector2(posx,posy);

	m_label = new ButtonLabel();

	if (m_label->init (m_name + "_label",pos,font,text,r,g,b,true))		
		m_label->setParent(this);	
	

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
		{
			Renderer::Instance().DrawImage( m_pushImage, pos.x, pos.y );
		}
		else if( !m_pushed )
		{
			Renderer::Instance().DrawImage( m_normalImage, pos.x, pos.y );
		}
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
		m_pushed = true;
		if (m_label)
			m_label->onInputEvent(message,true);

		break;

	case mtPointerButtonUp:
		if( m_pushed )
			NOTIFY_LISTENERS( onClick( this ) );		
		m_pushed = false;

		if (m_label)
			m_label->onInputEvent(message,true);

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