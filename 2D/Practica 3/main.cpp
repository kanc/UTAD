#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"


int main(int argc, char* argv[]) 
{
	float angle = 0;
	float scalefactor = 0;
	float mousex, mousey;
	bool crece = true;

	Screen::Instance().Open(800, 600, false);
		
	Image * pBall = ResourceManager::Instance().LoadImage("data//ball.png",1,1);
	pBall->SetMidHandle();

	while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC) ) {

		mousex = Screen::Instance().GetMouseX();
		mousey = Screen::Instance().GetMouseY();
		
		Renderer::Instance().Clear();

		Renderer::Instance().DrawImage(pBall,mousex,mousey,1,pBall->GetWidth() * scalefactor,pBall->GetHeight() * scalefactor,WrapValue(angle,360));

		angle+= Screen::Instance().ElapsedTime() * 30;
		
		if (crece)
			scalefactor+= Screen::Instance().ElapsedTime() * 2;
		else		
			scalefactor-= Screen::Instance().ElapsedTime() * 2;

		if (scalefactor > 5)
			crece = false;

		if (scalefactor < 0.5f)
			crece = true;				

		Screen::Instance().Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}

