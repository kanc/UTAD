#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

void primeraPartePractica();
void segundaPartePractica();

int main(int argc, char* argv[]) 
{
	Screen &screen = Screen::Instance();
	const Renderer &render = Renderer::Instance();

	screen.Open(800, 600, false);		
	
	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) ) {
		
		render.Clear();

		primeraPartePractica();
		//segundaPartePractica();		

		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}

void primeraPartePractica()
{
	const Renderer &render = Renderer::Instance();
	Screen &screen = Screen::Instance();

	float radius = 40;

	//franjas		
	render.SetBlendMode(Renderer::SOLID);
	render.SetColor(255,255,255,0);				
	render.DrawRect(screen.GetWidth() / 3, 0, screen.GetWidth() / 3, screen.GetHeight());		
		
	//solid		
	render.SetColor(255,0,0,0);				
	render.DrawEllipse(screen.GetWidth() / 2, screen.GetHeight() / 3, radius,radius);
	render.SetColor(0,255,0,0);
	render.DrawEllipse(screen.GetWidth() / 2 - radius / 2, screen.GetHeight() / 3 + radius / 2, radius,radius);
	render.SetColor(0,0,255,0);
	render.DrawEllipse(screen.GetWidth() / 2 + radius / 2, screen.GetHeight() / 3 + radius / 2, radius,radius);

	//alpha
	render.SetBlendMode(Renderer::ALPHA);
	render.SetColor(255,0,0,128);				
	render.DrawEllipse(screen.GetWidth() / 6, screen.GetHeight() / 2, radius,radius);
	render.SetColor(0,255,0,128);
	render.DrawEllipse(screen.GetWidth() / 6 - radius / 2, screen.GetHeight() / 2 + radius / 2, radius,radius);
	render.SetColor(0,0,255,128);
	render.DrawEllipse(screen.GetWidth() / 6 + radius / 2, screen.GetHeight() / 2 + radius / 2, radius,radius);

	//multiplicative
	render.SetBlendMode(Renderer::MULTIPLICATIVE);
	render.SetColor(255,0,0,255);				
	render.DrawEllipse(screen.GetWidth() / 2, screen.GetHeight() * 2 / 3, radius,radius);
	render.SetColor(0,255,0,255);
	render.DrawEllipse(screen.GetWidth() / 2 - radius / 2, screen.GetHeight() * 2 / 3 + radius / 2, radius,radius);
	render.SetColor(0,0,255,255);
	render.DrawEllipse(screen.GetWidth() / 2 + radius / 2, screen.GetHeight() * 2 / 3 + radius / 2, radius,radius);

	//aditive
	render.SetBlendMode(Renderer::ADDITIVE);
	render.SetColor(255,0,0,255);				
	render.DrawEllipse(screen.GetWidth() * 5 / 6, screen.GetHeight() / 2, radius,radius);
	render.SetColor(0,255,0,255);
	render.DrawEllipse(screen.GetWidth() * 5 / 6 - radius / 2, screen.GetHeight() / 2 + radius / 2, radius,radius);
	render.SetColor(0,0,255,255);
	render.DrawEllipse(screen.GetWidth() * 5 / 6 + radius / 2, screen.GetHeight() / 2 + radius / 2, radius,radius); 

}

void segundaPartePractica()
{
	const Renderer &render = Renderer::Instance();
	Screen &screen = Screen::Instance();

	Image *caja = ResourceManager::Instance().LoadImage(String ("data/box.jpg"));
	Image *luz = ResourceManager::Instance().LoadImage(String ("data/light.png"));

	int aModoOrigen[6] = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
	int aModoDestino[6] = {GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j ++)
		{
			render.SetBlendMode(Renderer::SOLID);				
			render.DrawImage(caja, j * caja->GetWidth(), i * caja->GetHeight());

			glBlendFunc(aModoDestino[j],aModoOrigen[i]);				
			render.DrawImage(luz, j * luz->GetWidth(), i * luz->GetHeight());
		}			
}


