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
	blendMode = Renderer::ALPHA;
	r = g = b = a = 0;
	collided = rotating = moving = scaling = false;
	toAngle = rotatingSpeed = anglesToRotate = 0;
	toX = toY = movingSpeedX = movingSpeedY = 0;
	scalingSpeedX = scalingSpeedY = 0;
	scalex = scaley = 1;
	prevX = prevY = 0;

	collision = NULL;
	colPixelData = NULL;
	colSprite = NULL;

}

Sprite::Sprite()
{
	this->image = NULL;	
	x = y = z = 0;
	colx = coly = colwidth = colheight = 0;
	angle = radius = 0;
	scalex = scaley =  0;
	animFPS = firstFrame = lastFrame = currentFrame = 0;
	blendMode = Renderer::ALPHA;
	r = g = b = a = 0;
	collided = rotating = moving = scaling = false;
	toAngle = rotatingSpeed = anglesToRotate = 0;
	toX = toY = movingSpeedX = movingSpeedY = 0;
	scalingSpeedX = scalingSpeedY = 0;
	scalex = scaley = 1;
	prevX = prevY = 0;

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
			
	//giramos en sentido horario
	if ( WrapValue(toAngle - this->angle,360) > WrapValue(this->angle - toAngle,360))
	{	rotatingSpeed = speed * -1;		
		anglesToRotate = WrapValue(this->angle - toAngle,360);
	}
	else //giramos en sentido antihorario
	{	rotatingSpeed = speed;
		anglesToRotate = WrapValue(toAngle - this->angle,360);
	}

	rotating = true;

}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	
	toX = x;
	toY = y;
	prevX = this->x;
	prevY = this->y;

	if (speedX == 0) //para evitar divisiones por 0
		speedX = 1;

	//si no se especifica la distancia vertical...
	if (speedY == 0)
	{
		//calculamos el modulo del vector del punto de origen al destino
		double distance = sqrt( ((toX - prevX) * (toX - prevX)) + ((toY - prevY) * (toY - prevY)) );
		//el tiempo necesario para recorrerlo sera la distancia entre la velocidad horizontal
		double timeRequired = distance / speedX;
		//calculamos nuestras velocidades homogeneas en base a este tiempo...  V = E / T
		speedX = abs((toX - prevX) / timeRequired);
		speedY = abs((toY - prevY) / timeRequired);
	}
	
	if (toX < prevX)
		movingSpeedX = speedX * -1;
	else
		movingSpeedX = speedX;

	if (toY < prevY)
		movingSpeedY = speedY * -1;
	else
		movingSpeedY = speedY;	

	moving = true;
}

void Sprite::ScaleTo(double scalex, double scaley, double speedX, double speedY )
{
	if (speedY == 0)
		scalingSpeedY = speedX;
	else
		scalingSpeedY = speedY;
	
	scalingSpeedX = speedX;

	
	if (scalex < 1 )
		scalingSpeedX = scalingSpeedX * -1;

	if (scaley < 1 )
		scalingSpeedY = scalingSpeedY * -1;

	toScaleX = scalex;
	toScaleY = scaley;
	
	scaling = true;

}

void Sprite::Update(double elapsed, const Map* map) {
			
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion	
	currentFrame+=elapsed * animFPS;
		
	if (currentFrame > lastFrame)
		currentFrame = firstFrame;
	
	// TAREA: Actualizar rotacion animada
	if (rotating)
	{		
		angle+=elapsed * rotatingSpeed;
		angle= WrapValue(angle,360);

		anglesToRotate-=abs(elapsed * rotatingSpeed);

		if (anglesToRotate <= 0)
			rotating = false;					
	}

	// TAREA: Actualizar movimiento animado
	if (moving)
	{
		x+= elapsed * movingSpeedX;
		y+= elapsed * movingSpeedY;

		if ((movingSpeedX > 0 && x >= toX) || (movingSpeedX < 0 && x <= toX))
			x = toX;

		if ((movingSpeedY > 0 && y >= toY) || (movingSpeedY < 0 && y <= toY))
			y = toY;

		if (x == toX && y == toY)
			moving = false;					
	}

	//ESCALADO	
	if (scaling)
	{
		scalex+= elapsed * scalingSpeedX;
		scaley+= elapsed * scalingSpeedY;

		if ((scalingSpeedX > 0 && scalex >= toScaleX) || (scalingSpeedX < 0 && scalex <= toScaleX))
			scalex = toScaleX;

		if ((scalingSpeedY > 0 && scaley >= toScaleY) || (scalingSpeedY < 0 && scaley <= toScaleY))
			scaley = toScaleY;

		if (scalex == toScaleX && scaley == toScaleY)
			scaling = false;		
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {

	Renderer::Instance().SetBlendMode(this->blendMode);
	Renderer::Instance().SetColor(GetRed(), GetGreen(), GetBlue(), GetAlpha());
	Renderer::Instance().DrawImage(this->image,x,y,(uint32)currentFrame,(double)(image->GetWidth() * scalex), (double)(image->GetHeight() * scaley), WrapValue(angle,360));
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
