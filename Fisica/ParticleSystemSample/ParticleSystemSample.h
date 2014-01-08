#ifndef	HEADER_H
#define HEADER_H
#include "vector.h"
#include "display.h"

//-----------------------------------------------------------------------------

struct tColor { float r,g,b ; };
struct 	tParticle
{
	tParticle *next, *prev; // enlaces con otras partículas
	tVector pos; // posición actual
	tVector prevPos; // posición anterior
	tVector vel; // dirección actual
    float mass; //masa de la particula
	float radius; // radio de la particula
	int life; // tiempo de vida
	tColor color; // color actual
	tColor prevColor; // color anterior
	tColor deltaColor; // delta para cambio de color
	GLuint index;//openGL index
};

struct 	tParticlePool
{
	tParticle* head;
};

struct tEmitter
{
	long id; // ID del emisor
	char name[80]; // nombre del emisor
	long flags; // banderas del emisor
	// Información de enlaces
	tEmitter *prev; // apuntador al padre
	tEmitter *next; // apuntador al hijo
	// Información de transformación
	tVector pos; // posición XYZ
//	tMatrix orientacion; // orientacion del emisor
	tVector vel;// velicity
	float speedVar; //variación de velocidad
	// Partícula
	tParticle *particle; // Lista enlazada terminada en NULL para rapida inserccion y borrado en cualquier lugar de la ista
	int maxParticles; // Total emitidas en cualquier momento
	int particleCount; // Total emitidas en este momento
	int emitsPerFrame, emitVar; // Emitidas por frame y su variación
	int life, lifeVar; // tiempo de vida y su variación
	tColor startColor, startColorVar; // color actual
	// Física
	tVector forces; //fuerza de gravedad, viento, etc.
};
struct 	tCursor
{
	tVector pos; // posición actual
	tVector prevPos; // posición anterior
	float radius; // radio de la particula
	tColor color; // color actual
	tColor prevColor; // color anterior
	tColor deltaColor; // delta para cambio de color
	GLuint index;//openGL index
};

#endif