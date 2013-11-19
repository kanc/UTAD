#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	while ( Screen::Instance().IsOpened() ) {
		// TAREA: Pintar primitivas
		
		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	return 0;
}
