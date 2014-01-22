#include "../include/AudioSource.h"


AudioSource::AudioSource(AudioBuffer* buff)
{
	alGenSources(1, &source);	
	SetGain(1);
	SetPitch(1);
	SetLooping(false);
	SetPosition(0,0,0);
	SetVelocity(0,0,0);	

	alSourcei(source, AL_BUFFER, buff->GetBuffer());
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &source);
}
