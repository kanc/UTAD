#include "Slider.h"

Slider::Slider()
{
	m_actualValue = 0;
	m_imgBar = NULL;
	m_imgSelector = NULL;
	m_parent = NULL;
	m_spaceControls = 0;
	m_prevX = 0;	
	m_buttonPressed = false;
	m_visible = true;
}

bool Slider::init( const std::string name, const Vector2& position, const float size, const std::string font, const float maxValue, const float steps, const std::string& imgBar, 
			const std::string& imgBall, const std::string& imgBtnLeft, const std::string& imgBtnLeftPushed, const std::string& imgBtnLeftover, const std::string& imgBtnRight, 
			const std::string& imgBtnRightPushed, const std::string& imgBtnRightover)
{
	m_name = name;
	m_position = position;
	m_barSize = size;
	m_maxValue = maxValue;
	m_steps = steps;

	m_imgBar = ResourceManager::Instance().LoadImage(String(imgBar.c_str()));
	m_imgSelector = ResourceManager::Instance().LoadImage(String(imgBall.c_str()));	
	Image* imgLeft = ResourceManager::Instance().LoadImage(String(imgBtnLeft.c_str()));

	m_btnLeft = new Button();
	m_btnRight = new Button();			
	m_lblMin = new Label();
	m_lblMax = new Label();

	//instanciamos los botones
	bool btnleft = m_btnLeft->init(m_name + "_leftbtn", Vector2(0,0), imgBtnLeft, imgBtnLeftPushed,imgBtnLeft,imgBtnLeftover);
	bool btnrigth = m_btnRight->init(m_name + "_rightbtn", Vector2(imgLeft->GetWidth() + (m_spaceControls * 2) + size,0),imgBtnRight, imgBtnRightPushed, imgBtnRight,imgBtnRightover);

	Font* pFont = ResourceManager::Instance().LoadFont(String(font.c_str()));	
	
	String sMax = String::FromInt((int)m_maxValue);

	bool lblIni = m_lblMin->init(m_name + "_lblMin", Vector2(imgLeft->GetWidth() + m_spaceControls, imgLeft->GetHeight()),font,"0",255,255,255,false);
	bool lblEnd = m_lblMax->init(m_name + "_lblMax", Vector2(imgLeft->GetWidth() + (m_spaceControls * 2) + m_barSize - pFont->GetTextWidth(sMax), imgLeft->GetHeight()),font,sMax.ToCString(),255,255,255,false);	

	if (btnleft && btnrigth && m_imgBar && m_imgSelector && lblIni && lblEnd)
	{		
		m_lblMin->setParent(this);
		m_lblMax->setParent(this);		
		m_btnLeft->setParent(this);
		m_btnLeft->setEventListener(this);
		m_btnRight->setParent(this);
		m_btnRight->setEventListener(this);

		m_size = Vector2((m_btnLeft->getSize().x * 2) + m_barSize + (m_spaceControls * 2) , m_btnLeft->getSize().y );

		return true;
	}
	else
		return false;

}

void Slider::update()
{

}

void Slider::render()
{
	if (m_visible)
	{
		Vector2 pos = getAbsolutePosition();
		float selectorPos = ((m_barSize - m_imgSelector->GetWidth()) * m_actualValue / m_maxValue); //calculamos en el que posicion se pinta la imagen del selector

		//barrita en posicion... x: tamaño del boton + espaciado + posicion global / y: posicion absoluta + mitad tamaño imagen del boton - mitad imagen de la propia barrita
		Renderer::Instance().DrawTiledImage(m_imgBar, m_btnLeft->getSize().x + pos.x + m_spaceControls, pos.y + (m_btnLeft->getSize().y / 2) - (m_imgBar->GetHeight() / 2), m_barSize ,m_imgBar->GetHeight());	
		//selector en posicion... x: tamaño del boton + espaciado + posicion calculada / y: posicion absoluta + mitad tamaño imagen del boton - mitad imagen del selector
		Renderer::Instance().DrawImage(m_imgSelector,pos.x + m_btnLeft->getSize().x + m_spaceControls + selectorPos , pos.y + (m_btnLeft->getSize().y / 2) - (m_imgSelector->GetHeight() / 2));
	}
	
}

void Slider::onClick( Control* sender )
{
	if (sender == m_btnLeft)
	{
		m_actualValue -= (m_maxValue / m_steps);
		if (m_actualValue < 0) m_actualValue = 0;
	}

	if (sender == m_btnRight)
	{
		m_actualValue += (m_maxValue / m_steps);
		if (m_actualValue > m_maxValue) m_actualValue = m_maxValue;
	}

}

void Slider::onInputEvent( const Message& message )
{
	switch( message.type )
	{
		case mtPointerButtonDown:
			m_buttonPressed = true;
			break;

		case mtPointerButtonUp:
			NOTIFY_LISTENERS( onClick( this ) );
			m_buttonPressed = false;

			break;
		case mtPointerMove:
			const MessagePointerMove* messagePointer = static_cast<const MessagePointerMove*>(&message);			
			
			if (m_buttonPressed)
			{	
				float inc = m_maxValue / m_steps;
				m_actualValue +=  (messagePointer->x - m_prevX) / inc;
				
			}

			m_prevX = messagePointer->x;
			
			
			break;
	
	}		
}

void Slider::destroy()
{

}