#ifndef UGINE_AUDIOENGINE_H
#define UGINE_AUDIOENGINE_H

class AudioEngine 
{
	public:
		static AudioEngine& Instance();
		void Init();
		void Finish();

	protected:		
		AudioEngine(void) : device(0),context(0) {}
		~AudioEngine(void);

	private:
		static AudioEngine* engine;
		void* device;
		void* context;
};

#endif