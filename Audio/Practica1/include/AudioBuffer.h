#ifndef UGINE_AUDIOBUFFER_H
#define UGINE_AUDIOBUFFER_H

#include "../include/string.h"

class AudioBuffer
{
	public:
		AudioBuffer(const String& filename);
		~AudioBuffer(void);
		bool IsValid() const { return alBuffer != 0; }
		unsigned int GetBuffer() const { return alBuffer; }
		String GetFilename() const { return filename; }

	private:
		unsigned int alBuffer;
		String filename; 
};

#endif