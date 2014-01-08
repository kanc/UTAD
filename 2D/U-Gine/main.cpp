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
    SCML::Data data("samples/knight/knight.scml");
    data.log();
    
    FileSystem fs;
    fs.load(&data);
    printf("Loaded %zu images.\n", fs.images.size());
    
    list<Entity*> entities;
    for(map<int, SCML::Data::Entity*>::iterator e = data.entities.begin(); e != data.entities.end(); e++)
    {
        Entity* entity = new Entity(&data, e->first);
        entity->setFileSystem(&fs);
        //entity->setScreen(screen);
        entities.push_back(entity);
    }
    printf("Loaded %zu entities.\n", entities.size());
    
    float x = 400.0f;
    float y = 300.0f;
    float angle = 0.0f;
    float scale = 1.0f;
    bool flipped = false;
    bool drawObjectPositions = false;
    bool drawBones = false;
    
    bool paused = false;
    
    bool done = false;

	for(list<Entity*>::iterator e = entities.begin(); e != entities.end(); e++)
    {
        (*e)->startAnimation(rand()%data.getNumAnimations((*e)->entity));
    }

    while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) 
	{
        renderer.Clear();
		

        if(!paused)
        {
            for(list<Entity*>::iterator e = entities.begin(); e != entities.end(); e++)
            {
				(*e)->update(screen.ElapsedTime() * 1000);
            }
        }
                
        
        for(list<Entity*>::iterator e = entities.begin(); e != entities.end(); e++)
        {
            (*e)->draw(x, y, angle, (flipped? -scale : scale), scale);
        }

        screen.Refresh();
	}

    ResourceManager::Instance().FreeResources();

	return 0;
}


