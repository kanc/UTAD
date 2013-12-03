/************************************************************************************************************/
//
//
/************************************************************************************************************/

#ifndef UGINE_INPUTMANAGER_H
#define UGINE_INPUTMANAGER_H

#include "string.h"

// códigos que representan los distintos tipos de inputs posibles
enum eInputCode
{
  // Teclado
  Key_Space = 32,  
  Key_0 = 48, 
  Key_1 = 49,
  Key_2 = 50,
  Key_3 = 51,
  Key_4 = 52,
  Key_5 = 53,
  Key_6 = 54,
  Key_7 = 55,
  Key_8 = 56,
  Key_9 = 57,
  Key_A = 65,
  Key_B = 66,
  Key_C = 67,
  Key_D = 68,
  Key_E = 69,
  Key_F = 70,
  Key_G = 71,
  Key_H = 72,
  Key_I = 73,
  Key_J = 74,
  Key_K = 75,
  Key_L = 76,
  Key_M = 77,
  Key_N = 78,
  Key_O = 79,
  Key_P = 80,
  Key_Q = 81,
  Key_R = 82,
  Key_S = 83,
  Key_T = 84,
  Key_U = 85,
  Key_V = 86,
  Key_W = 87,
  Key_X = 88,
  Key_Y = 89,
  Key_Z = 90,
  Key_LeftShift = 240,
  Key_LeftControl = 241,  
  Key_LeftAlt = 242,  
  Key_Escape = 256,
  Key_Enter = 257,  
  Key_Tab = 258,  
  Key_Backspace = 259,
  Key_Insert = 260,
  Key_Delete = 261,  
  Key_RightArrow = 262,
  Key_LeftArrow = 263,   
  Key_DownArrow = 264,
  Key_UpArrow = 265,
  Key_PageUp = 266,  
  Key_PageDown = 267,
  Key_Home = 268,
  Key_End = 269,  
  Key_CapsLock = 280,   
  Key_Pause = 284,    
  Key_F1 = 290,
  Key_F2 = 291,
  Key_F3 = 292,
  Key_F4 = 293,
  Key_F5 = 294,
  Key_F6 = 295,
  Key_F7 = 296,
  Key_F8 = 297,
  Key_F9 = 298,
  Key_F10 = 299,
  Key_F11 = 300,
  Key_F12 = 301,  
  Key_Keypad0 = 320,
  Key_Keypad1 = 321,
  Key_Keypad2 = 322,
  Key_Keypad3 = 323,
  Key_Keypad4 = 324,
  Key_Keypad5 = 325,
  Key_Keypad6 = 326,
  Key_Keypad7 = 327,
  Key_Keypad8 = 328,
  Key_Keypad9 = 329,
  Key_RightShift = 344,
  Key_RightControl = 345,  
  Key_RightAlt = 346,    
      

  // Ratón
  Mouse_Button0 = 0,
  Mouse_Button1 = 1,
  Mouse_Button2 = 2,
  Mouse_WheelDown,
  Mouse_WheelUp,
  Mouse_Down,
  Mouse_Up,
  Mouse_Left,
  Mouse_Right,
};

enum eInputType
{
	Keyboard,
	Mouse,
	Pad,
};

enum eButtonState
{
	btnUp,
	btnDown,
	btnPressed,
};

struct VirtualButton
{
	String name;
	Array <uint16> codes;

	VirtualButton() { }
	VirtualButton(const String& nam, eInputCode button) { name = nam; codes.Add(button); }
};

struct ButtonState
{
	eInputCode code;
	eButtonState state;
};

struct VirtualAxis
{
	String name;
	eInputCode positiveAxis;
	eInputCode negativeAxis;

	VirtualAxis() { }
	VirtualAxis(const String& nam, eInputCode posAxis,eInputCode negAxis) { name = nam; positiveAxis = posAxis; negativeAxis = negativeAxis; }
};

class InputManager
{
	private:
				
		//static InputManager *inputMng;
		Array<VirtualButton> _aVirtualButtons;
		Array<VirtualAxis> _aVirtualAxis;
		Array<ButtonState> _aButtonStates;

		VirtualButton GetMyVirtualButton(const String &name) const;
		VirtualAxis GetMyVirtualAxis(const String &name)const;
		eInputType GetInputType(eInputCode code) const;
		bool AddNewButtonToAction(const String &name, const eInputCode code);
		
		

	public:
		InputManager();
		~InputManager();
		//static const InputManager& Instance() { if ( !inputMng ) inputMng = new InputManager(); return *inputMng; }

	// Inicialición: deteccción de dispostivos, inicialización de los mismos... etc
    bool Init();

	// Cierre
    void End();

	// Devuelve true si el manager ha sido inicializado correctamente
	bool IsOk();

	// Función de actualización, actualización de estados entre frames
    void Update();
    

    // Crea un botón virtual
    void CreateVirtualButton( const String& name, eInputCode button );
	// Crea un eje virtual
    void CreateVirtualAxis( const String& name, eInputCode positiveAxis, eInputCode negativeAxis );

    // Está el botón pulsado en este momento?
    bool IsVirtualButtonPressed( const String& name ) const;
	// Devuelve true durante el frame que que el usuario ha comenzaco la pulsación de un botón
    bool IsVirtualButtonDown( const String& name ) const;
	// Devuelve true durante el frame que que el usuario ha dejado de pulsar un botón
    bool IsVirtualButtonUp( const String& name ) const;

    // Estado de ejes virtuales normalizado de -1 a +1
    float GetVirtualAxis( const String& name ) const;

    // Está el la tecla pulsada en este momento?
    bool IsKeyPressed( eInputCode vkCode );
	// Devuelve true durante el frame que que el usuario ha comenzaco la pulsación de una tecla (***OPCIONAL***)
    bool IsKeyDown( eInputCode vkCode );
	// Devuelve true durante el frame que que el usuario ha dejado de pulsar una tecla (***OPCIONAL***)
    bool IsKeyUp( eInputCode vkCode );

	// Está el la el botón del ratón tecla pulsado en este momento?
    bool IsMouseButtonPressed( eInputCode button );
	// Devuelve true durante el frame que que el usuario ha comenzaco la pulsación del botón del ratón dado
    bool GetMouseButtonDown( eInputCode button );
	// Devuelve true durante el frame que que el usuario ha dejado de pulsar el botón del ratón dado
    bool GetMouseButtonUp( eInputCode button );
};


#endif