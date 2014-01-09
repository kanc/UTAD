#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);

using namespace rapidxml;


Map::Map(const String &filename, uint16 firstColId) {
	// TAREA: Implementar constructor
	this->filename = filename;
	this->firstColId = firstColId;
	valid = false;

	String file = String::Read(filename);
	xml_document<> xmlparser;
	xmlparser.parse<0>((char *)file.ToCString());

	//guardamos los datos del mapa
	xml_node<>* nodeMap = xmlparser.first_node("map");

	width = atoi(nodeMap->first_attribute("width")->value());
	height = atoi(nodeMap->first_attribute("height")->value());
	tileWidth = atoi(nodeMap->first_attribute("tilewidth")->value());
	tileHeight = atoi(nodeMap->first_attribute("tileheight")->value());

	//guardamos los datos del tileset
	xml_node<>* nodeTileset = nodeMap->first_node("tileset");

	uint16 firstgid = atoi(nodeTileset->first_attribute("firstgid")->value());
	uint16 tWidth = atoi(nodeTileset->first_attribute("tilewidth")->value());
	uint16 tHeight = atoi(nodeTileset->first_attribute("tileheight")->value());
	uint16 offsX,offsY;	
	offsX = offsY = 0;
	//guardamos el offset
	xml_node<>* nodeOffset = nodeTileset->first_node("tileoffset");

	if (nodeOffset)
	{
		offsX = atoi(nodeOffset->first_attribute("x")->value());
		offsY = atoi(nodeOffset->first_attribute("y")->value());
	}

	//guardamos los datos del fichero de imagen
	xml_node<>* nodeImg = nodeTileset->first_node("image");
	this->imageFile = String( (char *)nodeImg->first_attribute("source")->value() );
	uint16 imgWidth = atoi(nodeImg->first_attribute("width")->value());
	uint16 imgHeight = atoi(nodeImg->first_attribute("height")->value());

	//gestionamos solo la primera capa de tiles
	xml_node<>* nodeData = nodeMap->first_node("layer")->first_node("data");

	//comprobamos que no haya codificacion en "data" y en tal caso salimos con valid=false
	xml_attribute<>* eleEnc = nodeData->first_attribute("enconding");
	xml_attribute<>* eleComp = nodeData->first_attribute("compresion");

	if (eleEnc || eleComp)
		return;
	
	//guardamos los tiles
	xml_node<>* nodeTile = nodeData->first_node("tile");

	while (nodeTile)
	{
		//cogemos el id del tile y le restamos el valor firstgid
		int16 tid = atoi(nodeTile->first_attribute("gid")->value());
		tid -= firstgid;

		this->tileIds.Add(tid);

		nodeTile = nodeTile->next_sibling("tile");
	}

	this->imageFile = filename.ExtractDir() + "/" + this->imageFile;

	//el numero de frames lo obtenemos dividiendo el ancho/alto de la imagen por el ancho/alto del tile
	this->image = ResourceManager::Instance().LoadImage(imageFile, imgWidth / tWidth, imgHeight / tHeight );
	this->image->SetHandle(offsX, offsY);

	tileBuffer = new bool[tileWidth * tileHeight];
	collisionMode = Sprite::CollisionMode::COLLISION_RECT;

	valid = true;

}

void Map::Render() const {
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				Renderer::Instance().SetColor(255,255,255,255);
				Renderer::Instance().DrawImage(image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
			}
		}
	}
}

bool Map::CheckCollision(const Collision* collision) const {
	// Creamos caja de colisiones
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol(&boxX, &boxY, &boxWidth, &boxHeight);
		
	

	// Comprobamos colision con cada tile
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= firstColId ) {
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if (collisionMode == Sprite::CollisionMode::COLLISION_PIXEL)
				{
					GetTileBitmap(x,y,tileBuffer);
					CollisionPixelData colPixel = CollisionPixelData(tileBuffer);
					if ( collision->DoesCollide(&colPixel,boxX,boxY) )
						return true;					
					
				}
				else
					if ( collision->DoesCollide(&boxCol) )
						return true;
					
			}
		}
	}
		
	return false;
}

double Map::GetGroundY(double x, double y) const {
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= width*tileWidth  ||  y >= height*tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/tileHeight); tiley < height; tiley++ ) {
		if ( tileIds[tiley*width + int(x/tileWidth)] >= firstColId ) {
			groundY = tiley*tileHeight;
			break;
		}
	}
	return groundY;
}

void Map::setCollisionMode( Sprite::CollisionMode colMode )
{
	collisionMode = colMode;

	if (collisionMode == Sprite::CollisionMode::COLLISION_PIXEL)
	{
		int comp;
			
		bitmap = stbi_load(imageFile.ToCString(), &imgWidth, &imgHeight, &comp, 4);		
	
	}
}

void Map::GetTileBitmap(uint32 x, uint32 y, bool* tilebuffer) const
{
	if (bitmap)
	{			
		for (uint32 j = y; j < y + tileHeight; j++)
			for (uint32 i = x; i < x + tileWidth; i++)
				tilebuffer[(j * tileHeight) + i] = bitmap[(j * imgWidth) + x + i + 3];		
	}
}