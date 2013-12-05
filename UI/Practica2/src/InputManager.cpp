#include "../include/InputManager.h"
#include "../include/screen.h"

InputManager* InputManager::inputMng = NULL;

InputManager::InputManager()
{		
}

InputManager::~InputManager()
{
    _aVirtualButtons.Clear();
	_aVirtualAxis.Clear();
	delete inputMng;

}

float InputManager:: GetMouseYAxis()
{
	float yAxis;

	yAxis = Screen::Instance().GetMouseY() - prevMouseY;
	prevMouseY = Screen::Instance().GetMouseY();

	return yAxis / Screen::Instance().GetDesktopHeight();

}

float InputManager:: GetMouseXAxis()
{
	float xAxis;

	xAxis = Screen::Instance().GetMouseX() - prevMouseX;

	prevMouseX = Screen::Instance().GetMouseX();

	return xAxis / Screen::Instance().GetDesktopWidth();

}

InputManager& InputManager::Instance() 
{ 
	if ( !inputMng ) 
		inputMng = new InputManager(); 
	
	return *inputMng; 
}


float InputManager::GetVirtualAxis( const String& name ) const
{
	VirtualAxis axis = GetMyVirtualAxis(name);
	float value = 0;

	switch (GetInputType(axis.positiveAxis)) //suponemos que positivo y negativo corresponden al mismo dispositivo
	{
		case eInputType::Mouse:
			if (axis.negativeAxis == eInputCode::Mouse_X )
				
			break;
			

	}

	return 0;
}

void InputManager::Update()
{

}

 void InputManager::CreateVirtualButton( const String& name, eInputCode button )
 {	 	 	 
	 if (!AddNewButtonToAction(name,button))
	 {
		 VirtualButton action(name,button);	 //si no creamos la accion
		_aVirtualButtons.Add(action);
	 }
 }

 bool InputManager::AddNewButtonToAction(const String &name, const eInputCode code)
 {
	for (uint16 i = 0; i < _aVirtualButtons.Size(); i++)
	{
		if (_aVirtualButtons[i].name == name)
		{	 
			_aVirtualButtons[i].codes.Add(code);
			return true;
		}
	}

	 return false;
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

	 for (uint16 i = 0; i < button.codes.Size(); i++)
	 {
		 switch (GetInputType((eInputCode)button.codes[i]))
		{
			case eInputType::Keyboard:
				pressed = Screen::Instance().KeyPressed(button.codes[i]);
				break;

			case eInputType::Mouse:
				pressed = Screen::Instance().MouseButtonPressed(button.codes[i]);
				break;

			case eInputType::Pad:
				pressed = false;
				break;
		}
	 }
	 
	 return pressed;
 }

 VirtualButton InputManager::GetMyVirtualButton(const String &name) const
 {	 	 
	 for (uint16 i = 0; i < _aVirtualButtons.Size(); i++)
	 {
		 if (_aVirtualButtons[i].name == name)
			 return _aVirtualButtons[i];
	 }
	 return VirtualButton();
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
	 if (code < 10)
		 return eInputType::Mouse;
	 else
		return eInputType::Keyboard;
 }