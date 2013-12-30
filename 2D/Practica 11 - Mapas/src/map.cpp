#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map(const String &filename, uint16 firstColId) {
	// TAREA: Implementar constructor
	this->filename = filename;
	this->firstColId = firstColId;
	valid = false;

	String file = String::Read(filename);
	xml_document<> xmlparser;
	xmlparser.parse<0>((char *)file.ToCString());

	xml_node<>* nodeMap = xmlparser.first_node("map");

	width = atoi(nodeMap->first_attribute("width")->value());
	height = atoi(nodeMap->first_attribute("height")->value());
	tileWidth = atoi(nodeMap->first_attribute("tilewidth")->value());
	tileHeight = atoi(nodeMap->first_attribute("tileheight")->value());

	xml_node<>* nodeTile = nodeMap->first_node("tileset");

	uint32 firstgid = atoi(nodeTile->first_attribute("firstgid")->value());
	uint32 tWidth = atoi(nodeTile->first_attribute("tilewidth")->value());
	uint32 tHeight = atoi(nodeTile->first_attribute("tileheight")->value());
	uint32 x,y;

	xml_node<>* nodeOffset = nodeTile->first_node("tileoffset");

	if (nodeOffset)
	{
		x = atoi(nodeOffset->first_attribute("x")->value());
		y = atoi(nodeOffset->first_attribute("y")->value());
	}



}

void Map::Render() const {
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
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
		if ( tileIds[tiley*width + int(x/tileWidth)] >= 0 ) {
			groundY = tiley*tileHeight;
			break;
		}
	}
	return groundY;
}
