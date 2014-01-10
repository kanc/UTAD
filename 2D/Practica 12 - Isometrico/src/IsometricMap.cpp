#include "../include/IsometricMap.h"
#include "../lib/rapidxml.hpp"
#include "../include/math.h"
#include "../include/image.h"
#include "../include/IsometricScene.h"

using namespace rapidxml;

IsometricMap::IsometricMap(const String& filename, uint16 firstColId) : Map(filename, firstColId)
{	
	
	String file = String::Read(filename);
	xml_document<> xmlparser;
	xmlparser.parse<0>((char *)file.ToCString());

	//guardamos los datos del mapa
	xml_node<>* nodeMap = xmlparser.first_node("map");

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

	//gestionamos la segunda capa de tiles
	xml_node<>* nodeData = nodeMap->first_node("layer")->next_sibling()->first_node("data");

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

		topLayerIds.Add(tid);

		nodeTile = nodeTile->next_sibling("tile");
	}

	//ajustamos el handle de la imagen cargada en la clase padre ¿?
	GetImage()->SetHandle(GetImage()->GetHandleX() + GetTileWidth(), GetImage()->GetHeight() - GetImage()->GetHandleY() - GetTileHeight());

	valid = true;
}

void IsometricMap::GenerateLayerSprites(IsometricScene* scene)
{	
	
	for (uint16 i = 0; i < GetRows(); i++)
		for (uint16 j = 0; j < 	GetColumns(); j++)	
		{	
			uint32 idTile = GetLayerId(j,i);
			if ( idTile >= 0) //si son tiles validos
			{	
				Sprite* topSprite = scene->CreateSprite(GetImage()); //cargamos el sprite con la imagen padre			
				topSprite->SetCurrentFrame(idTile); //le decimos que su frame actual es el correspondiente al id del tile
				topSprite->SetPosition(j * GetTileWidth(), i * GetTileHeight()); //lo posicionamos en la escena de acuerdo a la fila y columna del mapa
			
				//definimos la colision para los sprites de tiles colisionables
				if (idTile >= GetFirstColId())				
					topSprite->SetCollision(Sprite::CollisionMode::COLLISION_RECT);				
			}
		}
	
}

void IsometricMap::Render() const
{	

	for ( uint16 y = 0; y < GetRows(); y++ ) 
		for ( uint16 x = 0; x < GetColumns(); x++ ) 
		{			
			uint32 idTile = GetLayerId(x, y);
			if ( idTile >= 0 ) 
			{
				Renderer::Instance().SetColor(255,255,255,255);
				double xtile,ytile;
				TransformIsoCoords(x*GetTileWidth(),y*GetTileHeight(),0,&xtile, &ytile);
				Renderer::Instance().DrawImage(GetImage(), xtile, ytile, GetLayerId(x, y));
			}
		}	
}

int32 IsometricMap::GetLayerId(uint16 column, uint16 row) const
{
	return topLayerIds[row * GetColumns() + column];
}
