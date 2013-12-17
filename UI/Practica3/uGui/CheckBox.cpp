#include "CheckBox.h"

Checkbox::Checkbox()
{
	m_checked = false;
	m_spaceControl = 5;
}

bool Checkbox::init( const std::string name, const Vector2& position, const std::string text, const std::string font, uint8 r, uint8 g, uint8 b, const std::string& checkedImg, const std::string& uncheckedImg, const std::string& disableImg)
{
	m_name = name;
	m_position = position;

	m_imgChecked = ResourceManager::Instance().LoadImage(checkedImg.c_str());
	m_imgUnchecked = ResourceManager::Instance().LoadImage(uncheckedImg.c_str());
	
	m_checkLabel = new Label();
	bool lbl = m_checkLabel->init(m_name + "_label", position, font, text, r, g, b, false);
	m_checkLabel->setParent(this);
	m_checkLabel->setPosition(Vector2(0, (m_imgChecked->GetHeight() / 2) - (m_checkLabel->getSize().y / 2)));

	if (lbl && m_imgChecked && m_imgUnchecked)
	{
		
		m_size = Vector2(m_checkLabel->getSize().x + m_imgChecked->GetWidth() + m_spaceControl, m_imgChecked->GetHeight());
		return true;
	}
	else
		return false;

}

void Checkbox::update()
{

}

void Checkbox::render()
{
	if (m_visible)
	{
		Vector2 pos = getAbsolutePosition();

		m_checkLabel->render();

		if (m_checked)
			Renderer::Instance().DrawImage(m_imgChecked, pos.x + m_checkLabel->getSize().x + m_spaceControl, pos.y );
		else
			Renderer::Instance().DrawImage(m_imgUnchecked, pos.x + m_checkLabel->getSize().x + m_spaceControl, pos.y) ;
	}

}

void Checkbox::onInputEvent( const Message& message )
{
	switch( message.type )
	{
		case mtPointerButtonUp:
			if( m_enabled )
				if (m_checked)
					m_checked = false;
				else
					m_checked = true;

				NOTIFY_LISTENERS( onClick( this ) );			
		break;
	}
}

void Checkbox::destroy()
{

}