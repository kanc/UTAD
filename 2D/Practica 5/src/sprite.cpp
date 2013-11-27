#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include <math.h>
#include "../include/screen.h"

Sprite::Sprite(Image* image) {
	
	this->image = image;
	x = y = z = 0;
	colx = coly = colwidth = colheight = 0;
	angle = radius = 0;
	scalex = scaley =  0;
	animFPS = firstFrame = lastFrame = currentFrame = 0;
	blendMode = Renderer::SOLID;
	r = g = b = a = 0;
	collided = rotating = moving = false;
	toAngle = rotatingSpeed = anglesToRotate = 0;
	toX = toY = movingSpeedX = movingSpeedY = 0;
	prevX = prevY = 0;
	delay = 0;

	collision = NULL;
	colPixelData = NULL;
	colSprite = NULL;

}

Sprite::~Sprite() {
    // TAREA: Implementar
}

void Sprite::SetCollision(CollisionMode mode) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(Sprite* sprite) {
	return false;
}

bool Sprite::CheckCollision(const Map* map) {
	return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
	// TAREA: Implementar
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	
	toX = x;
	toY = y;
	movingSpeedX = speedX;
	movingSpeedY = speedY;

	moving = true;
}

void Sprite::Update(double elapsed, const Map* map) {
			
	double frametime;

	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion
	delay += elapsed;
	frametime = 1.0f / animFPS;

	Screen::Instance().SetTitle(String::FromFloat(delay));

	if (delay > frametime)
	{	
		currentFrame++;
		
		if (currentFrame > lastFrame)
			currentFrame = firstFrame;

		delay = 0;
	}
	
	// TAREA: Actualizar rotacion animada
	if (rotating)
	{
	}	

	// TAREA: Actualizar movimiento animado
	if (moving)
	{
		x+= movingSpeedX;
		y+= movingSpeedY;
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
	Renderer::Instance().SetBlendMode(this->blendMode);
	Renderer::Instance().DrawImage(this->image,x,y,currentFrame);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
