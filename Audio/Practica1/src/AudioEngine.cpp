#include "../include/AudioEngine.h"
#include "AL/al.h"
#include "AL/alc.h"


AudioEngine* AudioEngine::engine = 0;

AudioEngine& AudioEngine::Instance()
{
	if (!engine)
		return *engine;
	else
	{
		engine = new AudioEngine();
		return *engine;
	}
}

void AudioEngine::Init()
{
	device = (ALCdevice*)alcOpenDevice(0);
	context = (ALCcontext*)alcCreateContext((ALCdevice*)device, 0);

	alcMakeContextCurrent((ALCcontext*)context);
}

void AudioEngine::Finish()
{
	alcDestroyContext((ALCcontext*)context);
	alcCloseDevice((ALCdevice*)device);
}