#ifndef	HEADER_H
#define HEADER_H
#include "vector.h"
#include "display.h"

//-----------------------------------------------------------------------------

struct tColor { float r,g,b ; };
struct 	tParticle
{
	tParticle *next, *prev; // enlaces con otras part�culas
	tVector pos; // posici�n actual
	tVector prevPos; // posici�n anterior
	tVector vel; // direcci�n actual
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
	// Informaci�n de enlaces
	tEmitter *prev; // apuntador al padre
	tEmitter *next; // apuntador al hijo
	// Informaci�n de transformaci�n
	tVector pos; // posici�n XYZ
//	tMatrix orientacion; // orientacion del emisor
	tVector vel;// velicity
	float speedVar; //variaci�n de velocidad
	// Part�cula
	tParticle *particle; // Lista enlazada terminada en NULL para rapida inserccion y borrado en cualquier lugar de la ista
	int maxParticles; // Total emitidas en cualquier momento
	int particleCount; // Total emitidas en este momento
	int emitsPerFrame, emitVar; // Emitidas por frame y su variaci�n
	int life, lifeVar; // tiempo de vida y su variaci�n
	tColor startColor, startColorVar; // color actual
	// F�sica
	tVector forces; //fuerza de gravedad, viento, etc.
};
struct 	tCursor
{
	tVector pos; // posici�n actual
	tVector prevPos; // posici�n anterior
	float radius; // radio de la particula
	tColor color; // color actual
	tColor prevColor; // color anterior
	tColor deltaColor; // delta para cambio de color
	GLuint index;//openGL index
};

#endif