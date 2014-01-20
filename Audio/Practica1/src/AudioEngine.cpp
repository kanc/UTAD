#include "../include/AudioEngine.h"
#include "AL/al.h"
#include "AL/alc.h"

AudioEngine* AudioEngine::engine = nullptr;

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
	device = (ALCdevice*)alcOpenDevice(nullptr);
	context = (ALCcontext*)alcCreateContext((ALCdevice*)device, nullptr);

	alcMakeContextCurrent((ALCcontext*)context);
}

void AudioEngine::Finish()
{
	alcDestroyContext((ALCcontext*)context);
	alcCloseDevice((ALCdevice*)device);
}