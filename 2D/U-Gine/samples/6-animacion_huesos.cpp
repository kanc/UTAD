#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();

    screen.Open(screen.GetDesktopWidth(), screen.GetDesktopHeight(), true);
    //screen.Open(800, 600, false);

    SkeletonSprite sprite("data/anims/animation.xml");
    sprite.SetFPS(32);

    renderer.SetBlendMode(Renderer::ALPHA);
    while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) {
        renderer.Clear(0, 0, 0);
		
        sprite.SetPosition(screen.GetMouseX(), screen.GetMouseY());
        sprite.Update(screen.ElapsedTime());
        sprite.Render();

        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}
