#ifndef UGINE_LISTENER_H
#define UGINE_LISTENER_H

#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"

class Listener
{
	public:
		static Listener& Instance();

		void SetPosition(float x, float y, float z) { alListener3f (AL_POSITION, x, y, z); }
		void SetVelocity(float x, float y, float z) { alListener3f (AL_POSITION, x, y, z); }
		void SetOrientation(float x, float y, float z) { alListener3f (AL_POSITION, x, y, z); }

	protected:
		Listener() { SetPosition(0,0,0); SetVelocity(0,0,0); SetOrientation(0,0,0); }
		~Listener() {}
	
	private:
		static Listener* listener;
};

#endif