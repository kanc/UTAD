#ifndef UGINE_RENDERER_H_
#define UGINE_RENDERER_H_

#include "u-gine.h"
#include "SCMLpp.h"

namespace SCML_Ugine
{
    
	class FileSystem : public SCML::FileSystem
	{
		public:
    
		// Folder, File
		SCML_MAP(SCML_PAIR(int, int), Image*) images;
    
		virtual ~FileSystem();
		virtual bool loadImageFile(int folderID, int fileID, const std::string& filename);
		virtual void clear();
		virtual SCML_PAIR(unsigned int, unsigned int) getImageDimensions(int folderID, int fileID) const;
    
		Image* getImage(int folderID, int fileID) const;
    
	};

	class Entity : public SCML::Entity
	{
	    public:
    
	    FileSystem* file_system;
    
		Entity();
		Entity(SCML::Data* data, int entity, int animation = 0, int key = 0);
    
		FileSystem* setFileSystem(FileSystem* fs);
    
		virtual void convert_to_SCML_coords(float& x, float& y, float& angle);
		virtual SCML_PAIR(unsigned int, unsigned int) getImageDimensions(int folderID, int fileID) const;
		virtual void draw_internal(int folderID, int fileID, float x, float y, float angle, float scale_x, float scale_y);
	};

}

#endif
