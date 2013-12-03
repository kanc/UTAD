#include "../include/InputManager.h"
#include "../include/screen.h"

InputManager::InputManager()
{	

	//glfwSetKeyCallback( &MyKeyCallback );
}

InputManager::~InputManager()
{
    _aVirtualButtons.Clear();
	_aVirtualAxis.Clear();
//	delete inputMng;

}

/*void GLFWCALL MyKeyCallback( int k, int action )
{
   
   g_pApp->KeyStateChange( k, (action==GLFW_PRESS) );
}

glfwSetKeyCallback( &MyKeyCallback );


*/

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

  float InputManager::GetVirtualAxis( const String& name ) const
 {	 
	 VirtualAxis axis = GetMyVirtualAxis(name);

	 //normalizar los ejes
	 return 0;
	 
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