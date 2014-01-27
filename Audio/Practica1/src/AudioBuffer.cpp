#include "../include/AudioBuffer.h"
#include "../include/file.h"
#include "AL/al.h"
#include "AL/alc.h"

AudioBuffer::AudioBuffer(const String& filename) : alBuffer(0)
{
	File audiofile = File(filename, FILE_READ);

	//leemos el bloque ChunkID
	char* field = new char[5];
	field[4] = '\0';
	audiofile.ReadBytes(field,4);

	if (String(field) != "RIFF") //si ese bloque no es RIFF, no es un wave correcto	
	{	delete[] field;
		return;
	}

	//leemos el chunksize
	audiofile.ReadInt();
	//leemos el bloque Format
	audiofile.ReadBytes(field,4);

	if (String(field) != "WAVE") //si ese bloque no es WAVE, no es un wave correcto		
	{	delete[] field;
		return;
	}	
	
	//leemos el bloque SubChunkId
	audiofile.ReadBytes(field,4);

	if (String(field) != "fmt ") //si ese bloque no es fmt , no es un wave correcto		
	{	delete[] field;
		return;
	}	
		
	//leemos el SubChunkSize
	audiofile.ReadInt();
	
	//leemos el AudioFormat
	uint16 audioFormat = audiofile.ReadInt16();
	bool extraParams = false;
	if (audioFormat != 16 && audioFormat != 1)
		extraParams = true;

	//leemos el Channels
	uint16 channels = audiofile.ReadInt16();
	//leemos el SampleRate
	uint32 sampleRate = audiofile.ReadInt();
	//leemos el ByteRate
	audiofile.ReadInt();
	//leemos el BlockAlign
	audiofile.ReadInt16();	
	//leemos el BitsPerSample
	audiofile.ReadInt16();

	//leemos el Extraparamsize
	uint16 paramSize = audiofile.ReadInt16();	

	//si hay parametros extra los leemos tambien
	if (extraParams)						
		audiofile.ReadBytes(0,paramSize);	

	//ahora leemos los datos miscelaneas que pueda haber (autor, estilo, etc...) hast encontrar el bloque "data"	
	do
	{
		audiofile.ReadBytes(field, 4);
	}
	while (String(field) != "data");

	uint32 dataSize = audiofile.ReadInt();
	
	char* soundbytes = new char[dataSize];
	audiofile.ReadBytes(soundbytes,dataSize);
	
	//creamos un buffer de openAL y guardamos el identificador en nuestra variable miembro
	alGenBuffers(1, &alBuffer);
	//modificamos los datos del buffer y
	alBufferData(alBuffer, channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, soundbytes, dataSize, sampleRate);

	this->filename = filename;

	delete[] soundbytes;
	delete[] field;

}

AudioBuffer::~AudioBuffer(void)
{

}