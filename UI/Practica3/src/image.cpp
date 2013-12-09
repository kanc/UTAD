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

		if (!glfwExtensionSupported("GL_ARB_texture_non_power_of_two"))
		{
			//log2 de x es el numero que tenemos que elevar a 2 para que nos de x, si x no es potencia de 2, entocnes el resultado no sera un numero entero
			//con lo cual ceil, que devuelve el primero entero no menor de un numero nos devolver la potencia de 2 mayor y mas cercana.
			//si este numero lo elevamos a dos, ya tenemos nuestro nuevo tamaño.
			double nuevoAncho = pow(2,ceil(Log2(x))); 
			double nuevoAlto = pow(2,ceil(Log2(y)));

			if (nuevoAncho != x || nuevoAlto != y)						
			{	
				unsigned char *newbuffer = ManageImageBuffer(buffer,height,width,nuevoAlto,nuevoAncho);
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,nuevoAncho,nuevoAlto,0,GL_RGBA,GL_UNSIGNED_BYTE,newbuffer);

				lastU = (double)width / nuevoAncho;
				lastV = (double)height / nuevoAlto;
			
				delete newbuffer;
			}
			else		
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
		}
		else
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
		
		delete buffer;		
	}

	//SetMidHandle();

}

Image::~Image() {

	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {

	glBindTexture(GL_TEXTURE_2D, gltex);
}

unsigned char * Image::ManageImageBuffer(unsigned char *buffer, int actualHeight, int actualWidth, int newHeight, int newWidth)
{
	unsigned char *newBuffer = new unsigned char[newHeight * newWidth * 4];	
	memset(newBuffer,0,newHeight * newWidth * 4);
	
	for (int y = 0; y < actualHeight; y++) //recorremos las lineas verticales
	{	for (int x = 0; x < actualWidth; x++) //recorremos las lineas horizontales de 4 en 4 (tamaño de nuestro pixel)
		{
			newBuffer[(y * newWidth * 4) + (x * 4)] = buffer[(y * actualWidth * 4) + (x * 4)]; //R
			newBuffer[(y * newWidth * 4) + (x * 4) + 1] = buffer[(y * actualWidth * 4) + (x * 4) + 1]; //G
			newBuffer[(y * newWidth * 4) + (x * 4) + 2] = buffer[(y * actualWidth * 4) + (x * 4)+ 2]; //B
			newBuffer[(y * newWidth * 4) + (x * 4) + 3] = buffer[(y * actualWidth * 4 ) + (x * 4) + 3]; //A
		}
	}
	
	return newBuffer;
}
