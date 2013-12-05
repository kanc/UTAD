#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


#include "include/u-gine.h"
#include "include/InputManager.h"
#include <Windows.h>
#include <Xinput.h>

#pragma comment (lib, "XInput9_1_0.lib")

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();
	InputManager &im = InputManager::Instance();

	screen.Open(800, 600, false);

	Image *imgalien = new Image("data/alien.png"); //ResourceManager::Instance().LoadImage("data/alien.png");
	Sprite &alien = Sprite(imgalien);
	
	alien.SetX(100);
	alien.SetY(100);
	
	im.CreateVirtualButton(String("moveright"),eInputCode::Key_D);	
	im.CreateVirtualButton(String("moveleft"),eInputCode::Key_A);
	im.CreateVirtualButton(String("moveup"),eInputCode::Key_W);
	im.CreateVirtualButton(String("movedown"),eInputCode::Key_S);
	im.CreateVirtualButton(String("pickmove"),eInputCode::Mouse_Button0);

	glfwWaitEvents();

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {				

		render.Clear();

		XINPUT_STATE state;

		ZeroMemory(&state,sizeof(XINPUT_STATE));

		XInputGetState(0,&state);

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			Beep(5000,100);
		}

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			XINPUT_VIBRATION vib;
			ZeroMemory(&vib,sizeof(XINPUT_VIBRATION));

			vib.wLeftMotorSpeed = 20000;
			XInputSetState(0,&vib);
		}

		float xp = (float) state.Gamepad.sThumbLX / 32768;
		float yp = (float) state.Gamepad.sThumbLY / 32768;
		
		if (abs((int)xp * 1000) < 3000)
			xp =0;

		if (abs((int)yp * 1000) < 3000)
			yp =0;

		alien.MoveTo(alien.GetX() + (xp * 10), alien.GetY() - (yp * 10),150);

		if (im.IsVirtualButtonPressed("moveright"))
			alien.MoveTo(alien.GetX() + 1, alien.GetY(),50);

		if (im.IsVirtualButtonPressed("moveleft"))
			alien.MoveTo(alien.GetX() - 1, alien.GetY(),50);

		if (im.IsVirtualButtonPressed("moveup"))
			alien.MoveTo(alien.GetX(), alien.GetY() - 1,50);

		if (im.IsVirtualButtonPressed("movedown"))
			alien.MoveTo(alien.GetX(), alien.GetY() + 1,50);

		if (im.IsVirtualButtonPressed("pickmove"))
			alien.MoveTo(screen.GetMouseX(),screen.GetMouseY(),50);

		alien.Update(screen.ElapsedTime(),NULL);
		alien.Render();

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}

