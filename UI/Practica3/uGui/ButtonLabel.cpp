#include "ButtonLabel.h"

void ButtonLabel::onInputEvent( const Message& message, const bool fromButton )
{
	switch( message.type )
	{
		case mtPointerButtonDown:
			m_pushed = true;
			
			if (!fromButton) 
				m_parent->onInputEvent(message);

			break;

		case mtPointerButtonUp:
			if( m_pushed )
				NOTIFY_LISTENERS( onClick( this ) );
			m_pushed = false;

			if (!fromButton) 
				m_parent->onInputEvent(message);

			break;
	}
}