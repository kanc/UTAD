#include "Singleton.h"
#include "Message.h"
#include "Vector2.h"
#include <map>
#include <string>

using namespace std;

class Control;

class GUIManager : public Singleton<GUIManager>
{
public:  

	int init();
	void end();

	void update();
	void render();

	void setRootControl( Control* control );
	Control* getRootControl();

	void injectInput( const Message& message );

	Vector2 getScreenSize() const;

	Control* findControlByName( const string& name );
	void deleteControl( const string& name );

protected:

	Control*							m_rootControl;
};
