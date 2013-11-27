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
	
	toAngle = WrapValue(angle,360);	
	
	anglesToRotate = WrapValue( toAngle - this->angle,360);	

	if ( WrapValue(toAngle - this->angle,360) > WrapValue( this->angle - toAngle,360))
		rotatingSpeed = speed * -1;
	else
		rotatingSpeed = speed;

	rotating = true;

}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	
	toX = x;
	toY = y;
	movingSpeedX = speedX;
	movingSpeedY = speedY;

	moving = true;
}

void Sprite::Update(double elapsed, const Map* map) {
			
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion
	Screen::Instance().SetTitle(String::FromFloat(anglesToRotate));

	currentFrame+=elapsed * animFPS;
		
	if (currentFrame > lastFrame)
		currentFrame = firstFrame;
	
	// TAREA: Actualizar rotacion animada
	if (rotating)
	{		
		angle+=elapsed * rotatingSpeed;
		angle= WrapValue(angle,360);
		anglesToRotate-=elapsed * rotatingSpeed;

		if (anglesToRotate <= 0)
			rotating = false;
	}

	// TAREA: Actualizar movimiento animado
	if (moving)
	{
		x+= movingSpeedX;
		y+= movingSpeedY;

		if (x == toX && y == toY)
			moving = false;
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
	Renderer::Instance().SetBlendMode(this->blendMode);
	Renderer::Instance().DrawImage(this->image,x,y,(uint32)currentFrame,image->GetWidth() * scalex, image->GetHeight() * scaley, WrapValue(angle,360));
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
