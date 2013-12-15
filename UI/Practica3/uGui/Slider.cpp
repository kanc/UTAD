#include "Slider.h"

Slider::Slider()
{
	m_actualValue = 0;
	m_imgBar = NULL;
	m_imgSelector = NULL;
	m_parent = NULL;
	m_spaceControls = 5;
}

bool Slider::init( const std::string name, const Vector2& position, const float size, const float maxValue, const float steps, const std::string& imgBar, 
			const std::string& imgBall, const std::string& imgBtnLeft, const std::string& imgBtnLeftPushed, const std::string& imgBtnRight, const std::string& imgBtnRightPushed )
{
	m_name = name;
	m_position = position;
	m_size = size;
	m_maxValue = maxValue;
	m_steps = steps;

	m_imgBar = ResourceManager::Instance().LoadImage(String(imgBar.c_str()));
	m_imgSelector = ResourceManager::Instance().LoadImage(String(imgBall.c_str()));

	m_btnLeft = new Button();
	m_btnRight = new Button();
		
	Image* imgLeft = ResourceManager::Instance().LoadImage(String(imgBtnLeft.c_str()));

	bool btnleft = m_btnLeft->init(m_name + "_leftbtn", Vector2(0,0), imgBtnLeft, imgBtnLeftPushed);
	bool btnrigth = m_btnRight->init(m_name + "_rightbtn", Vector2(imgLeft->GetWidth() + (m_spaceControls * 2) + size,0),imgBtnRight, imgBtnRightPushed);

	if (btnleft && btnrigth && m_imgBar && m_imgSelector)
	{
		m_btnLeft->setParent(this);
		m_btnRight->setParent(this);
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
	Vector2 pos = getAbsolutePosition();
	float selectorPos = (m_maxValue / m_steps) * m_actualValue;

	m_btnLeft->render();
	m_btnRight->render();

	Renderer::Instance().DrawTiledImage(m_imgBar, m_btnLeft->getSize().x + pos.x + m_spaceControls, pos.y + (m_btnLeft->getSize().y / 2), m_size ,m_imgBar->GetHeight() );	
	Renderer::Instance().DrawImage(m_imgSelector,m_btnLeft->getSize().x + m_spaceControls + pos.x + selectorPos , pos.y + (m_btnLeft->getSize().y / 2) - (m_imgSelector->GetHeight() / 2));
	

}

void Slider::onInputEvent( const Message& message )
{

}

void Slider::destroy()
{
}