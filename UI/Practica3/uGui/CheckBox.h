#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_

#include "Control.h"
#include "Label.h"

class Checkbox : public Control
{
	public:
		Checkbox();
		bool init( const std::string name, const Vector2& position, const std::string text, const std::string font, uint8 r, uint8 g, uint8 b, const std::string& checkedImg, const std::string& uncheckedImg, const std::string& disableImg);

		virtual void update();
		virtual void render();
		virtual void onInputEvent( const Message& message );
		virtual void destroy();

		void setChecked (bool check) { m_checked = check; }
		string getText() { return m_checkLabel->GetText(); }
		void setText(string text) { m_checkLabel->SetText(text); }
		void setTextColor (uint8 r, uint8 g, uint8 b) { m_checkLabel->SetColor(r,g,b); }
		bool isChecked() { return m_checked; }

	private:
		bool m_checked;
		float m_spaceControl;
		Label* m_checkLabel;
		Image * m_imgChecked;
		Image * m_imgUnchecked;
};

#endif
