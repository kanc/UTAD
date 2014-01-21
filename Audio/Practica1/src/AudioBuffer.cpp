#include "../include/AudioBuffer.h"
#include "../include/file.h"
#include "AL/al.h"
#include "AL/alc.h"

AudioBuffer::AudioBuffer(const String& filename) : alBuffer(0)
{
	File* audiofile = new File(filename, FILE_READ);

	//leemos el bloque ChunkID
	char* chunkid = new char[5];
	chunkid[4] = '\0';
	audiofile->ReadBytes(chunkid,4);

	if (String(chunkid) != "RIFF") //si ese bloque no es RIFF, no es un wave correcto
	{	delete[] chunkid;
		return;
	}
	delete[] chunkid;

	//leemos el chunksize
	audiofile->ReadInt();

	//leemos el bloque Format
	char* format = new char[5];
	format[4] = '\0';
	audiofile->ReadBytes(format,4);

	if (String(format) != "WAVE") //si ese bloque no es WAVE, no es un wave correcto		
	{	delete[] format;
		return;
	}
	delete[] format;
	
	//leemos el bloque SubChunkId
	char* subchunk = new char[5];
	subchunk[4] = '\0';
	audiofile->ReadBytes(subchunk,4);

	if (String(subchunk) != "fmt ") //si ese bloque no es fmt , no es un wave correcto		
	{	delete[] subchunk;
		return;
	}
	delete[] subchunk;
		
	//leemos el SubChunkSize
	audiofile->ReadInt();
	
	//leemos el AudioFormat
	uint16 audioFormat = audiofile->ReadInt16();
	bool extraParams = false;
	if (audioFormat != 16 && audioFormat != 1)
		extraParams = true;

	//leemos el Channels
	uint16 channels = audiofile->ReadInt16();
	//leemos el SampleRate
	uint32 sampleRate = audiofile->ReadInt();
	//leemos el ByteRate
	audiofile->ReadInt();
	//leemos el BlockAlign
	audiofile->ReadInt16();	
	//leemos el BitsPerSample
	audiofile->ReadInt16();

	//leemos el Extraparamsize
	uint16 paramSize = audiofile->ReadInt16();	

	//si hay parametros extra los leemos tambien
	if (extraParams)						
		audiofile->ReadBytes(0,paramSize);	

	//ahora leemos los datos miscelaneas que pueda haber (autor, estilo, etc...) hast encontrar el bloque "data"
	char* data = new char[5];
	data[4] = '\0';
	
	do
	{
		audiofile->ReadBytes(data, 4);
	}
	while (String(data) != "data");

	uint32 dataSize = audiofile->ReadInt();
	
	char* soundbytes = new char[dataSize];
	audiofile->ReadBytes(soundbytes,dataSize);
	
	//creamos un buffer de openAL y guardamos el identificador en nuestra variable miembro
	alGenBuffers(1, &alBuffer);
	//modificamos los datos del buffer y
	alBufferData(alBuffer, channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, soundbytes, dataSize, sampleRate);

	delete[] soundbytes;

}

AudioBuffer::~AudioBuffer(void)
{

}