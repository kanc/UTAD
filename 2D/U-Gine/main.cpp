#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "include/SCML_Ugine.h"
#include "include/SCMLpp.h"
#include <vector>
#include <list>
#include <string>

using namespace SCML_Ugine;
using namespace std;

int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();

    screen.Open(800, 600, false);
    renderer.SetBlendMode(Renderer::ALPHA);

	size_t data_file_index = 0;
    SCML::Data data("data/monster/example.SCML");
    data.log();
    
    FileSystem fs;
    fs.load(&data);
    printf("Loaded %zu images.\n", fs.images.size());
    
    list<Entity*> entities;
    for(map<int, SCML::Data::Entity*>::iterator e = data.entities.begin(); e != data.entities.end(); e++)
    {
        Entity* entity = new Entity(&data, e->first);
        entity->setFileSystem(&fs);        
        entities.push_back(entity);
    }
    printf("Loaded %zu entities.\n", entities.size());
    
    float x = 300;
    float y = 100.0f;
    float angle = 0.0f;
    float scale = 1.0f;
	bool flip = false;

	for(list<Entity*>::iterator e = entities.begin(); e != entities.end(); e++)    
        (*e)->startAnimation(rand()%data.getNumAnimations((*e)->entity));

    while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) 
	{
        renderer.Clear(150,150,150);
		
		if (screen.KeyPressed(GLFW_KEY_UP))		
			y -= 100 * screen.ElapsedTime();

		else if (screen.KeyPressed(GLFW_KEY_DOWN))		
			y += 100 * screen.ElapsedTime();

		else if (screen.KeyPressed(GLFW_KEY_LEFT))		
		{	
			x -= 100 * screen.ElapsedTime();
			flip = true;
		}
		else if (screen.KeyPressed(GLFW_KEY_RIGHT))		
		{
			x += 100 * screen.ElapsedTime();
			flip = false;
		}

		if (screen.KeyPressed(GLFW_KEY_SPACE))					
			for(list<Entity*>::iterator e = entities.begin(); e != entities.end(); e++)    
				(*e)->startAnimation(rand()%data.getNumAnimations((*e)->entity));

		
        
        for(list<Entity*>::iterator e = entities.begin(); e != entities.end(); e++)
        {
			(*e)->update(screen.ElapsedTime() * 1000);
        }
                               
        for(list<Entity*>::iterator e = entities.begin(); e != entities.end(); e++)
        {
            if (!flip)
				(*e)->draw(x,  y, angle, scale);
			else
				(*e)->draw(x,  y, -angle, -scale);
        }

        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}


