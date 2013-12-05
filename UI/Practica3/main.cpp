#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
/*
int main(int argc, char* argv[]) {
Screen::Instance().Open(640, 480, false);

while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC) ) {
Screen::Instance().Refresh();
}

return 0;
}
*/

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "uGui/GUIManager.h"
#include "UGui/Button.h"
#include "uGui/Window.h"
#include "uGui/IEventListener.h"

void CreateGUI();
void MouseButtonCallback(int button, int action);
void MousePosCallback(int x, int y);

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
class Listener : public IEventListener
{
	void onClick( Control* sender )
	{
		printf( "onClick -> Control %s\n", sender->getName().c_str());
	}
};

Listener listener;


//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) 
{
	Screen::Instance().Open( 1024, 768, false );
	CreateGUI();

	glfwSetMouseButtonCallback(MouseButtonCallback);
	glfwSetMousePosCallback(MousePosCallback);

	while ( Screen::Instance().IsOpened()  &&  !Screen::Instance().KeyPressed(GLFW_KEY_ESC) ) 
	{
		GUIManager::instance().update();

		Renderer::Instance().Clear(0, 0, 0);
		GUIManager::instance().render();
		Screen::Instance().Refresh();
	}

	GUIManager::instance().end();

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void CreateGUI()
{
	// inicializa GUI
	GUIManager& uiManager = GUIManager::instance();
	uiManager.init();

	// Crea una ventana
	Window* window = new Window();
	window->init( "Ventana", Vector2(100,200), "data/GUI/Window4.png" );
	window->setEventListener( &listener );
	uiManager.setRootControl( window );

	// Crea un botón
	Button* b1 = new Button();
	b1->init( "Boton1", Vector2( 200, 100 ), "data/GUI/Button_Normal.png", "data/GUI/Button_Push.png" );
	b1->setEventListener( &listener );
	b1->setParent( GUIManager::instance().getRootControl() );

	// Crea un botón
	Button* b2 = new Button(); 
	b2->init( "Boton2", Vector2( 200, 150 ), "data/GUI/Button_Normal.png", "data/GUI/Button_Push.png" );   
	b2->setEventListener( &listener );
	b2->setParent( GUIManager::instance().getRootControl() );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void MouseButtonCallback(int button, int action)
{
	int x, y;
	glfwGetMousePos( &x, &y );

	if( action == GLFW_PRESS )
		GUIManager::instance().injectInput( MessagePointerButtonDown( button, (float)x, (float)y ) );
	else if( action == GLFW_RELEASE )
		GUIManager::instance().injectInput( MessagePointerButtonUp( button, (float)x, (float)y ) );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void MousePosCallback(int x, int y)
{
	GUIManager::instance().injectInput( MessagePointerMove( (float)x, (float)y ) ); 
}