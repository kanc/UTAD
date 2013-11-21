#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	while ( Screen::Instance().IsOpened() ) {
		
		Renderer::Instance().Clear(255,0,0);

		Renderer::Instance().SetColor(223,155,67,0);
		Renderer::Instance().DrawRect(16,16,768,568);

		Renderer::Instance().SetColor(123,55,67,0);
		Renderer::Instance().DrawEllipse(400,150,260,100);
		
		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	return 0;
}
