#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
    Screen::Instance().Open(640, 480, false);
    //Screen::Instance().Open(Screen::Instance().GetDesktopWidth(), Screen::Instance().GetDesktopHeight(), true);
    
    while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC) ) {
        Renderer::Instance().Clear(255, 255, 0);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        Renderer::Instance().DrawRect(16, 16, Screen::Instance().GetWidth()-32, Screen::Instance().GetHeight()-32);
        Renderer::Instance().SetColor(0, 255, 0, 255);
        Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/4, Screen::Instance().GetWidth()/2-32, Screen::Instance().GetHeight()/4-32);
        
		// Refrescamos la pantalla
        Screen::Instance().Refresh();
	}
    
	return 0;
}
