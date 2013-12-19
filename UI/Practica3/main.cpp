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
void createCreditsWindow();
void createExitWindow();
void createUI();
//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
enum eGameState
{
	eMainWindow,
	eNewGame,
	eSettings,
	eCredits,
	eExit,
	eEnd,
};

eGameState m_gameState;

class Listener : public IEventListener
{
	void onClick( Control* sender )
	{
		if (sender->getName() == "btnbegin")
			m_gameState = eNewGame;

		if (sender->getName() == "btnsettings")
			m_gameState = eSettings;

		if (sender->getName() == "btnbackToMain")
			m_gameState = eMainWindow;			

		if (sender->getName() == "btncredits")
			m_gameState = eCredits;			

		if (sender->getName() == "btnExit")
			m_gameState = eExit;			

		if (sender->getName() == "btnEnd")
			m_gameState = eEnd;			
		
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

	m_gameState = eMainWindow;	

	Image *img = ResourceManager::Instance().LoadImage("data/part.png");	
	img->SetMidHandle();
	Emitter *emitter = new Emitter(img,true);

	emitter->SetAngularVelocity(0,360);
	emitter->SetLifetime(1,1);
	emitter->SetMaxColor(255,255,255);
	emitter->SetMinColor(0,0,0);
	emitter->SetRate(500,800);
	emitter->SetVelocityX(-128,128);
	emitter->SetVelocityY(-128,128);		

	float VelEmitterX, VelEmitterY;
	VelEmitterX = VelEmitterY = 200;

	emitter->SetX(100);
	emitter->SetY(100);
	emitter->Start();

	while ( Screen::Instance().IsOpened()  &&  !Screen::Instance().KeyPressed(GLFW_KEY_ESC) && m_gameState!=eEnd ) 
	{		
		Renderer::Instance().Clear();

		emitter->SetX(emitter->GetX() + (VelEmitterX * Screen::Instance().ElapsedTime()));
		emitter->SetY(emitter->GetY() + (VelEmitterY * Screen::Instance().ElapsedTime()));
		
		if (emitter->GetX() >= Screen::Instance().GetWidth())
			VelEmitterX = - VelEmitterX;
		else if (emitter->GetX() <= 0)
			VelEmitterX = - VelEmitterX;	

		if (emitter->GetY() >= Screen::Instance().GetHeight())
			VelEmitterY = - VelEmitterY;
		else if (emitter->GetY() <= 0)
			VelEmitterY = - VelEmitterY;	
		
		GUIManager::instance().update();

		emitter->Update(Screen::Instance().ElapsedTime());
		emitter->Render();

		createUI();		
		GUIManager::instance().render();		

		Screen::Instance().Refresh();
	}
	emitter->Stop();
	delete emitter;

	GUIManager::instance().end();

	//hemos comentado los destroys de los objetos y liberamos nuestro contenido desde el resource manager
	ResourceManager::Instance().FreeResources();

	return 0;
}

void createUI()
{
	switch (m_gameState)
	{	
		case eMainWindow:
			if (GUIManager::instance().getRootControl())
				if (!GUIManager::instance().findControlByName("mainWnd"))
					createMainWindow();
			break;

		case eNewGame:
			if (GUIManager::instance().getRootControl())
			{	
				GUIManager::instance().deleteControl(GUIManager::instance().getRootControl()->getName());
				GUIManager::instance().setRootControl(NULL);
			}
				
			break;

		case eSettings:
			if (GUIManager::instance().getRootControl())
				if (!GUIManager::instance().findControlByName("settingsWnd"))
					createSettingsWindow();
			break;

		case eCredits:
			if (GUIManager::instance().getRootControl())
				if (!GUIManager::instance().findControlByName("creditsWnd"))
					createCreditsWindow();
			break;

		case eExit:
			if (GUIManager::instance().getRootControl())
				if (!GUIManager::instance().findControlByName("exitWnd"))
					createExitWindow();
			break;
			
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------

void createMainWindow()
{
	GUIManager& uiManager = GUIManager::instance();	

	//borramos los controles anteriores
	if (uiManager.getRootControl())
		uiManager.deleteControl(uiManager.getRootControl()->getName());

	
	Window* window = new Window();
	window->init( "mainWnd", Vector2(0,0), "data/GUI/Window.png" );	
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
	btnBegin->init("btnbegin", Vector2(xoffset, yoffset),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnBegin->addText("data/arial16_2.png","New Game",255,255,255);
	btnBegin->setParent(window);
	btnBegin->setEventListener(&listener);

	Button *btnSettings = new Button();
	btnSettings->init("btnsettings", Vector2(xoffset, btnBegin->getPosition().y + btnBegin->getSize().y + spaced ),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnSettings->addText("data/arial16_2.png","Settings",255,255,255);
	btnSettings->setParent(window);
	btnSettings->setEventListener(&listener);

	Button *btnCredits = new Button();
	btnCredits->init("btncredits", Vector2(xoffset, btnSettings->getPosition().y + btnSettings->getSize().y + spaced),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnCredits->addText("data/arial16_2.png","Credits",255,255,255);
	btnCredits->setParent(window);
	btnCredits->setEventListener(&listener);

	Button *btnExit = new Button();
	btnExit->init("btnExit", Vector2(xoffset, btnCredits->getPosition().y + btnCredits->getSize().y + spaced),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnExit->addText("data/arial16_2.png","Exit Game",255,255,255);
	btnExit->setParent(window);
	btnExit->setEventListener(&listener);	

}

void createExitWindow()
{
	GUIManager& uiManager = GUIManager::instance();	

	//borramos los controles anteriores
	if (uiManager.getRootControl())
		uiManager.deleteControl(uiManager.getRootControl()->getName());
	
	Window* window = new Window();
	window->init( "exitWnd", Vector2(0,0), "data/GUI/Window2.png" );	
	window->setEventListener( &listener );
	uiManager.setRootControl( window );
	window->setPosition(Vector2(Screen::Instance().GetWidth() / 2 - window->getSize().x / 2, Screen::Instance().GetHeight() / 2 - window->getSize().y / 2) );

	float spaced = 40;
	float xoffset = 75;
	float yoffset = 100;

	Label* titulo = new Label();
	titulo->init("maintitle",Vector2(xoffset * 1.5f,15),"data/arial16_2.png","Do you want to exit?",255,255,255,false);
	titulo->setParent(window);

	Button *btnBegin = new Button();
	btnBegin->init("btnEnd", Vector2(xoffset, yoffset),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnBegin->addText("data/arial16_2.png","Yes",255,255,255);
	btnBegin->setParent(window);
	btnBegin->setEventListener(&listener);

	Button *btnSettings = new Button();
	btnSettings->init("btnbackToMain", Vector2(xoffset, btnBegin->getPosition().y + btnBegin->getSize().y + spaced ),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnSettings->addText("data/arial16_2.png","No",255,255,255);
	btnSettings->setParent(window);
	btnSettings->setEventListener(&listener);

}

void createCreditsWindow()
{
	GUIManager& uiManager = GUIManager::instance();	

	//borramos los controles anteriores
	if (uiManager.getRootControl())
		uiManager.deleteControl(uiManager.getRootControl()->getName());
	
	float spaced = 40;
	float xoffset = 75;
	float yoffset = 100;

	Window* window = new Window();
	window->init( "creditsWnd", Vector2(0,0), "data/GUI/Window.png" );	
	window->setEventListener( &listener );
	uiManager.setRootControl( window );
	window->setPosition(Vector2(Screen::Instance().GetWidth() / 2 - window->getSize().x / 2, Screen::Instance().GetHeight() / 2 - window->getSize().y / 2) );

	Label* titulo = new Label();
	titulo->init("creditstitle",Vector2(xoffset * 2,15),"data/arial16_2.png","Credits",255,255,255,false);
	titulo->setParent(window);

	Label* grap = new Label();
	grap->init("credits1",Vector2(xoffset, yoffset),"data/arial16_2.png"," Graphics: David Escalona",255,255,255,false);
	grap->setParent(window);

	Label* prog = new Label();
	prog->init("progra",Vector2(xoffset, yoffset + grap->getSize().y + spaced),"data/arial16_2.png"," Lead Developer: Ignacio Martinez",255,255,255,false);
	prog->setParent(window);

	Label* progother = new Label();
	progother->init("prograc",Vector2(xoffset, prog->getPosition().y + prog->getSize().y + spaced),"data/arial16_2.png","Junior Developer: David Escalona",255,255,255,false);
	progother->setParent(window);

	Button *btnBack = new Button();
	btnBack->init("btnbackToMain", Vector2(xoffset, progother->getPosition().y + progother->getSize().y + (spaced * 4)),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
	btnBack->addText("data/arial16_2.png","Back",255,255,255);
	btnBack->setParent(window);
	btnBack->setEventListener(&listener);	


}

void createSettingsWindow()
{
	GUIManager& uiManager = GUIManager::instance();	

	//borramos los controles anteriores
	if (uiManager.getRootControl())
		uiManager.deleteControl(uiManager.getRootControl()->getName());

	float spaced = 40;
	float xoffset = 90;
	float yoffset = 100;
	
	Window* window = new Window();
	window->init( "settingsWnd", Vector2(0,0), "data/GUI/Window.png" );	
	window->setEventListener( &listener );
	uiManager.setRootControl( window );
	window->setPosition(Vector2(Screen::Instance().GetWidth() / 2 - window->getSize().x / 2, Screen::Instance().GetHeight() / 2 - window->getSize().y / 2) );

	Label* titulo = new Label();
	titulo->init("settingstitle",Vector2(xoffset * 1.75f,15),"data/arial16_2.png","Settings",255,255,255,false);
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

	Label* lblVol = new Label();
	lblVol->init("settingstitle",Vector2(xoffset,chkAutoSave->getPosition().y + chkAutoSave->getSize().y + spaced),"data/arial16_2.png","Volume",255,255,255,false);
	lblVol->setParent(window);

	Slider* sldVolumen = new Slider();
	sldVolumen->init("sldVolume",Vector2(xoffset + lblVol->getSize().x + spaced ,chkAutoSave->getPosition().y + chkAutoSave->getSize().y + spaced),100,"data/arial16_2.png",100,15,"data/GUI/sldbar.png","data/GUI/slider.png","data/GUI/sldleft.png","data/GUI/sldleft_p.png","data/GUI/sldleft_o.png","data/GUI/sldrigth.png","data/GUI/sldrigth_p.png","data/GUI/sldrigth_o.png");
	sldVolumen->setEventListener(&listener);
	sldVolumen->setParent(window);	

	Button *btnBack = new Button();
	btnBack->init("btnbackToMain", Vector2(xoffset, sldVolumen->getPosition().y + sldVolumen->getSize().y + (spaced * 2)),"data/GUI/boton.png","data/GUI/boton_p.png","data/GUI/boton.png","data/GUI/boton_o.png");
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