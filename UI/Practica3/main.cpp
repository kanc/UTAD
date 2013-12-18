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
#include "uGui/Label.h"
#include "uGui/IEventListener.h"
#include "uGui/Slider.h"
#include "uGui/CheckBox.h"

void CreateGUI();
void MouseButtonCallback(int button, int action);
void MousePosCallback(int x, int y);
void createMainWindow();
void createSettingsWindow();
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

	glfwSetMouseButtonCallback(MouseButtonCallback);
	glfwSetMousePosCallback(MousePosCallback);

	GUIManager::instance().init();

	createMainWindow();
	//createSettingsWindow();


	while ( Screen::Instance().IsOpened()  &&  !Screen::Instance().KeyPressed(GLFW_KEY_ESC) ) 
	{
		GUIManager::instance().update();

		Renderer::Instance().Clear(0, 0, 0);
		GUIManager::instance().render();		

		Screen::Instance().Refresh();
	}

	GUIManager::instance().end();

	//hemos comentado los destroys de los objetos y liberamos nuestro contenido desde el resource manager
	ResourceManager::Instance().FreeResources();

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void CreateGUI()
{
	// inicializa GUI
	/*GUIManager& uiManager = GUIManager::instance();
	uiManager.init();

	// Crea una ventana
	Window* window = new Window();
	window->init( "Ventana", Vector2(0,0), "data/GUI/Window4.png" );
	window->setEventListener( &listener );
	uiManager.setRootControl( window );

	// Crea un botón
	Button* b1 = new Button();
	b1->init( "Boton1", Vector2( 300, 100 ), "data/GUI/boton.png", "data/GUI/Button_Push.png", "data/GUI/Button_Disabled.png","");
	b1->setEventListener( &listener );
	b1->setParent( GUIManager::instance().getRootControl() );
	b1->addText("data/arial16_2.png","Boton",255,255,255);

	Checkbox *chk1 = new Checkbox();
	chk1->init("check1",Vector2(300, 200), "Opcion 1","data/arial16_2.png",255,255,255,"data/GUI/CheckBox_enabled.png","data/GUI/CheckBox_disabled.png","data/GUI/CheckBox_disabled.png");
	chk1->setParent(GUIManager::instance().getRootControl());	

	Slider* sl = new Slider();
	sl->init("slider1",Vector2(200,50),300,"data/arial16_2.png",100,15,"data/GUI/Slider_bar2.png","data/GUI/Slider_ball.png","data/GUI/Slider_Left_Normal.png","data/GUI/Slider_Left_Push.png","data/GUI/Slider_Right_Normal.png","data/GUI/Slider_Right_Push.png");
	sl->setEventListener(&listener);
	sl->setParent(GUIManager::instance().getRootControl());	*/
}


void createMainWindow()
{
	GUIManager& uiManager = GUIManager::instance();	

	//borramos los controles anteriores
	if (uiManager.getRootControl())
		uiManager.deleteControl(uiManager.getRootControl()->getName());

	
	Window* window = new Window();
	window->init( "mainw", Vector2(0,0), "data/GUI/Window.png" );	
	window->setEventListener( &listener );
	uiManager.setRootControl( window );
	window->setPosition(Vector2(Screen::Instance().GetWidth() / 2 - window->getSize().x / 2, Screen::Instance().GetHeight() / 2 - window->getSize().y / 2) );

	float spaced = 40;
	float xoffset = 75;
	float yoffset = 100;

	Label* titulo = new Label();
	titulo->init("maintitle",Vector2(xoffset * 2,15),"data/arial16_2.png","Main Menu",255,255,255,false);
	titulo->setParent(window);

	Button *btnBegin = new Button();
	btnBegin->init("begin", Vector2(xoffset, yoffset),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnBegin->addText("data/arial16_2.png","New Game",255,255,255);
	btnBegin->setParent(window);
	btnBegin->setEventListener(&listener);

	Button *btnSettings = new Button();
	btnSettings->init("settings", Vector2(xoffset, btnBegin->getPosition().y + btnBegin->getSize().y + spaced ),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnSettings->addText("data/arial16_2.png","Settings",255,255,255);
	btnSettings->setParent(window);
	btnSettings->setEventListener(&listener);

	Button *btnCredits = new Button();
	btnCredits->init("credits", Vector2(xoffset, btnSettings->getPosition().y + btnSettings->getSize().y + spaced),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnCredits->addText("data/arial16_2.png","Credits",255,255,255);
	btnCredits->setParent(window);
	btnCredits->setEventListener(&listener);

	Button *btnExit = new Button();
	btnExit->init("exit", Vector2(xoffset, btnCredits->getPosition().y + btnCredits->getSize().y + spaced),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnExit->addText("data/arial16_2.png","Exit Game",255,255,255);
	btnExit->setParent(window);
	btnExit->setEventListener(&listener);	

}

void createSettingsWindow()
{
	GUIManager& uiManager = GUIManager::instance();	

	//borramos los controles anteriores
	if (uiManager.getRootControl())
		uiManager.deleteControl(uiManager.getRootControl()->getName());

	float spaced = 7;
	float xoffset = 30;
	float yoffset = 60;
	
	Window* window = new Window();
	window->init( "settings", Vector2(0,0), "data/GUI/Window.png" );	
	window->setEventListener( &listener );
	uiManager.setRootControl( window );
	window->setPosition(Vector2(Screen::Instance().GetWidth() / 2 - window->getSize().x / 2, Screen::Instance().GetHeight() / 2 - window->getSize().y / 2) );

	Label* titulo = new Label();
	titulo->init("settingstitle",Vector2(xoffset,15),"data/arial16_2.png","Settings",255,255,255,false);
	titulo->setParent(window);

	Checkbox* chkGore = new Checkbox();
	chkGore->init("chkgore",Vector2(xoffset, yoffset), "Enable Gore Mode","data/arial16_2.png",255,255,255,"data/GUI/chkon.png","data/GUI/chkoff.png","data/GUI/chkoff.png");
	chkGore->setParent(window);
	chkGore->setEventListener(&listener);
	
	Checkbox* chkParticles = new Checkbox();
	chkParticles->init("chkparticle",Vector2(xoffset, chkGore->getPosition().y + chkGore->getSize().y + spaced), "Enable Particles","data/arial16_2.png",255,255,255,"data/GUI/chkon.png","data/GUI/chkoff.png","data/GUI/chkoff.png");
	chkParticles->setParent(window);
	chkParticles->setEventListener(&listener);
	
	Checkbox* chkAutoSave = new Checkbox();
	chkAutoSave->init("chkautosave",Vector2(xoffset, chkParticles->getPosition().y + chkParticles->getSize().y + spaced), "Enable Autosave","data/arial16_2.png",255,255,255,"data/GUI/chkon.png","data/GUI/chkoff.png","data/GUI/chkoff.png");
	chkAutoSave->setParent(window);
	chkAutoSave->setEventListener(&listener);

	Slider* sldVolumen = new Slider();
	sldVolumen->init("sldVolume",Vector2(xoffset,chkAutoSave->getPosition().y + chkAutoSave->getSize().y + spaced),300,"data/arial16_2.png",100,15,"data/GUI/sldbar.png","data/GUI/slider.png","data/GUI/sldleft.png","data/GUI/sldleft_p.png","data/GUI/sldleft_o.png","data/GUI/sldleft.png","data/GUI/sldleft_p.png","data/GUI/sldleft_o.png");
	sldVolumen->setEventListener(&listener);
	sldVolumen->setParent(window);	

	Button *btnBack = new Button();
	btnBack->init("exit", Vector2(xoffset, sldVolumen->getPosition().y + sldVolumen->getSize().y + (spaced * 4)),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnBack->addText("data/arial16_2.png","Back",255,255,255);
	btnBack->setParent(window);
	btnBack->setEventListener(&listener);	

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