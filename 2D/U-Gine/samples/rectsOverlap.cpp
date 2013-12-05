#include "Engine/Motor2D.h"
#include <sstream>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace std;

struct Rect {
	double x, y, width, height;

	Rect() : x(0), y(0), width(0), height(0) {}
	Rect(double x, double y, double width, double height) : x(x), y(y), width(width), height(height) {}
	void draw() { Renderer::instance().drawRect(x, y, width, height); }
};

int main(int argc, char* argv[]) {
	Screen& screen = Screen::instance();
	Renderer& renderer = Renderer::instance();

	screen.open(640, 480, false);

	Rect rect1(32, 32, 128, 128);
	Rect rect2(64, 64, 128, 128);
	Rect rect3;

	float xdir = 256.0f;
	float ydir = 256.0f;
	while (screen.isOpened()  &&  !screen.keyPressed(GLFW_KEY_ESC)) {
		rect1.x += xdir * screen.elapsedTime();
		rect2.y += ydir * screen.elapsedTime();
		if ( rect1.x <= 0 ) { xdir *= -1.0f; rect1.x = 0; }
		if ( rect1.x+rect1.width >= screen.getWidth() ) { xdir *= -1.0f; rect1.x = screen.getWidth()-rect1.width; }
		if ( rect2.y <= 0 ) { ydir *= -1.0f; rect2.y = 0; }
		if ( rect2.y+rect2.height >= screen.getHeight() ) { ydir *= -1.0f; rect2.y = screen.getHeight()-rect2.height; }
		
		if ( rectsOverlap(rect1.x, rect1.y, rect1.width, rect1.height, rect2.x, rect2.y, rect2.width, rect2.height) )
			overlappingRect(rect1.x, rect1.y, rect1.width, rect1.height, rect2.x, rect2.y, rect2.width, rect2.height, &rect3.x, &rect3.y, &rect3.width, &rect3.height);
		else
			rect3 = Rect(0, 0, 0, 0);

		renderer.clear();
		
		renderer.setColor(255, 0, 0, 255);
		rect1.draw();
		renderer.setColor(255, 255, 0, 255);
		rect2.draw();
		renderer.setColor(255, 128, 0, 255);
		rect3.draw();

		screen.refresh();
	}

	ResourceManager::instance().freeResources();

	return 0;
}