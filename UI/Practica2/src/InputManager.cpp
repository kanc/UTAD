#include "../include/InputManager.h"
#include "../include/screen.h"

InputManager::InputManager()
{

}

InputManager::InputManager()
{
    _aVirtualButtons.Clear();
	_aVirtualAxis.Clear();
	delete inputMng;

}

 void InputManager::CreateVirtualButton( const String& name, eInputCode button )
 {
	 VirtualButton action = VirtualButton(name,button);
	 
	 _aVirtualButtons.Add(action);
 }

 void InputManager::CreateVirtualAxis( const String& name, eInputCode positiveAxis, eInputCode negativeAxis )
 {
	 VirtualAxis axis = VirtualAxis(name,positiveAxis,negativeAxis);

	 _aVirtualAxis.Add(axis);
 }

 bool InputManager::IsVirtualButtonPressed( const String& name ) const
 {	 
	 bool pressed = false;
	 VirtualButton button = GetMyVirtualButton(name);

	 switch (GetInputType(button.code))
	 {
		case eInputType::Keyboard:
			pressed = Screen::Instance().KeyPressed(button.code);
			break;

		case eInputType::Mouse:
			pressed = Screen::Instance().MouseButtonPressed(button.code);
			break;

		case eInputType::Pad:
			pressed = false;
			break;
	 }
	 
	 return pressed;
 }

  float InputManager::GetVirtualAxis( const String& name ) const
 {	 
	 VirtualAxis axis = GetMyVirtualAxis(name);

	 //normalizar los ejes
	 
 }

 VirtualButton  InputManager::GetMyVirtualButton(const String &name) const
 {	 	 
	 for (uint16 i = 0; i < _aVirtualButtons.Size(); i++)
	 {
		 if (_aVirtualButtons[i].name == name)
			 return _aVirtualButtons[i];
	 }
 }

 VirtualAxis  InputManager::GetMyVirtualAxis(const String &name) const
 {	 	 
	 for (uint16 i = 0; i < _aVirtualAxis.Size(); i++)
	 {
		 if (_aVirtualButtons[i].name == name)
			 return _aVirtualAxis[i];
	 }
 }

 eInputType InputManager::GetInputType(eInputCode code) const
 {
	 return eInputType::Keyboard;
 }