#include "../include/CollisionPixelData.h"

extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);

CollisionPixelData::~CollisionPixelData()
{
	delete[] data;
}

bool CollisionPixelData::IsValid() const
{
	if (data)
		return true;
	else
		return false;
}

const String& CollisionPixelData::GetFilename() const
{
	return filename;
}

uint16 CollisionPixelData::GetWidth() const
{
	return width;
}

uint16 CollisionPixelData::GetHeight() const
{
	return height;
}

bool CollisionPixelData::GetData(uint32 x, uint32 y) const
{
	return data[(y * width) + x];
}

CollisionPixelData::CollisionPixelData(const String &filename) 
{
	int imgW, imgH, comp;
	
	this->filename = filename;

    unsigned char* buffer = stbi_load(filename.ToCString(), &imgW, &imgH, &comp, 4);
	
	if (buffer) 
	{
		width = (uint16)imgW;
		height = (uint16)imgH;

		data = new bool[width * height];

		for ( uint32 j = 0; j < height; j++ ) 
			for ( uint32 i = 0; i < width; i++ ) 
			{	
				if (buffer[(j * width + i) * 4 + 3] == 0)
					data[(j * width) + i] = false;
				else 
					data[(j * width) + i] = true;
			}
					
		stbi_image_free(buffer);
	}
}