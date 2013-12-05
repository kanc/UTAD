#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

#define NUMTRAILS 16

// Esta estructura define el rastro que deja la imagen
struct Trail {
	int32 x, y;
	float angle;

    Trail() : x(0), y(0), angle(0) {}
    Trail(int32 x, int32 y, float angle) : x(x), y(y), angle(angle) {}
};

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();

    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    //screen.Open(800, 600, false);
    renderer.SetBlendMode(Renderer::ALPHA);

	// Cargamos la imagen
    Image* image = ResourceManager::Instance().LoadImage("data/images/ball.png");
    image->SetMidHandle();
	
	float angle = 0;
	double accum = 0;
    Array<Trail> trails;
    while ( screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC) ) {
		// Actualizamos angulo de la imagen
        angle += 30 * screen.ElapsedTime();

		// Actualizamos los rastros
        accum += screen.ElapsedTime();
		if ( accum >= 0.05 ) {
            trails.Add(Trail(screen.GetMouseX(), screen.GetMouseY(), angle));
            if ( trails.Size() > NUMTRAILS ) {
                trails.RemoveAt(0);
				accum = 0;
			}
		}

		// Limpiamos fondo de pantalla
        renderer.Clear(0, 0, 0);

		// Dibujamos rastro
        for ( int i = 0; i < trails.Size(); i++ ) {
            renderer.SetColor(255, 255, 255, 256/(trails.Size()-i+1));
            renderer.DrawImage(image, trails[i].x, trails[i].y, 0, 0, 0, trails[i].angle);
		}

		// Dibujamos imagen
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawImage(image, screen.GetMouseX(), screen.GetMouseY(), 0, 0, 0, angle);

		// Refrescamos la pantalla
        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}
