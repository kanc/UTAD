#ifndef UGINE_AUDIOSOURCE_H
#define UGINE_AUDIOSOURCE_H

#include "AudioBuffer.h"
#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"

class AudioSource
{
	public:
		AudioSource(AudioBuffer* buffer);
		~AudioSource();

		void SetPitch(float pitch) { alSourcef(source, AL_PITCH, pitch); }
		void SetGain(float gain) { alSourcef(source, AL_GAIN, gain); }
		void SetLooping(bool loop) { alSourcei(source, AL_PITCH, loop); }
		void SetPosition(float x, float y, float z) { alSource3f(source, AL_POSITION, x, y, z); }
		void SetVelocity(float x, float y, float z) { alSource3f(source, AL_VELOCITY, x, y, z); }
		
		void Play() { alSourcePlay(source); }  
		void Stop() { alSourceStop(source); }  
		void Pause() { alSourcePause(source); }  
		bool IsPlaying() const { ALint playing;	alGetSourcei(source, AL_SOURCE_STATE, &playing); return playing == AL_PLAYING;  }

	private:
		unsigned int source;
		AudioBuffer* buffer;
};

#endif