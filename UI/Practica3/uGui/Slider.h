#ifndef _SLIDER_H_
#define _SLIDER_H_

#include "Control.h"
#include "Button.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"

class Slider : public Control
{
	public:
		Slider();

		bool init( const std::string name, const Vector2& position, const float size, const float maxValue, const float steps, const std::string& imgBar, 
			const std::string& imgBall, const std::string& imgBtnLeft, const std::string& imgBtnLeftPushed, const std::string& imgBtnRight, const std::string& imgBtnRightPushed );

		virtual void update();
		virtual void render();
		virtual void onInputEvent( const Message& message );
		virtual void destroy();

	private:
		float m_size;
		float m_maxValue;
		float m_actualValue;
		float m_steps;
		float m_spaceControls;

		Image* m_imgBar;
		Image* m_imgSelector;

		Button* m_btnLeft;
		Button* m_btnRight;
};


#endif