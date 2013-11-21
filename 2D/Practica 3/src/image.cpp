#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>


// TAREA: Declarar funciones de stb_image.c
extern "C"  unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);


Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;
	int x,y,comp;

	// TAREA: Cargar el buffer de la imagen
	unsigned char *buffer = stbi_load(this->filename.ToCString(), &x, &y,&comp,4);

	width = x;
	height = y;

	// Generamos la textura
	if ( buffer ) {
		// TAREA: Generar la textura de OpenGL
		glGenTextures(1,&gltex);

		glBindTexture(GL_TEXTURE_2D,gltex);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);

		delete buffer;
	}

}

Image::~Image() {
	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {

	glBindTexture(GL_TEXTURE_2D, gltex);
}
