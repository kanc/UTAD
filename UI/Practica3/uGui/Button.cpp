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
	m_size					= Vector2( (float)m_normalImage->GetWidth(), (float)m_normalImage->GetHeight() );

	return true;
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