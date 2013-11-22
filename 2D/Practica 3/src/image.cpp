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

		//log2 de x es el numero que tenemos que elevar a 2 para que nos de x, si x no es potencia de 2, entocnes el resultado no sera un numero entero
		//con lo cual ceil, que devuelve el primero entero no menor de un numero nos devolver la potencia de 2 mayor y mas cercana.
		//si este numero lo elevamos a dos, ya tenemos nuestro nuevo tamaño.
		double nuevoAncho = pow(2,ceil(Log2(x))); 
		double nuevoAlto = pow(2,ceil(Log2(y)));
														
		// TAREA: Generar la textura de OpenGL
		glGenTextures(1,&gltex);

		glBindTexture(GL_TEXTURE_2D,gltex);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		if (nuevoAncho != x || nuevoAlto != y)						
		{	
			unsigned char *newbuffer = ManageImageBuffer(buffer,y,x,nuevoAlto,nuevoAncho);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,newbuffer);
		}
		else		
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);

		
		//delete buffer;		
	}

}

Image::~Image() {

	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {

	glBindTexture(GL_TEXTURE_2D, gltex);
}

unsigned char * Image::ManageImageBuffer(unsigned char *buffer, int actualHeight, int actualWidth, int newHeight, int newWidth)
{
	unsigned char *newBuffer = new unsigned char(newHeight * newWidth * 4);	
	
	for (unsigned int height = 0; height < newHeight; height++) //recorremos las lineas verticales
	{	for (unsigned int width = 0; width < newWidth; width+=4) //recorremos las lineas horizontales de 4 en 4 (tamaño de nuestro pixel)
		{
			if (width < actualWidth) //si esta dentro del tamaño de la textura "real" pintamos en el nuevo buffer
			{
				newBuffer[(height * width) + width] = buffer[(height * width) + width]; //R
				newBuffer[(height * width) + width + 1] = buffer[(height * width) + width + 1]; //G
				newBuffer[(height * width) + width + 2] = buffer[(height * width) + width + 2]; //B
				newBuffer[(height * width) + width + 3] = buffer[(height * width) + width + 3]; //A
			}
			else //si esta fuera de tamaño de la imagen, escribimos pixel transparente
			{
				newBuffer[(height * width) + width] = 255; //R
				newBuffer[(height * width) + width + 1] = 0; //G
				newBuffer[(height * width) + width + 2] = 0; //B
				newBuffer[(height * width) + width + 3] = 150; //A
			}
		}
	}
	
	return newBuffer;
}
