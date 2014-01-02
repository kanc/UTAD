#include "../include/Particle.h"
#include "../include/sprite.h"

Particle::Particle() : Sprite(NULL)
{
	velocityx = 0;
	velocityy = 0;
	angularVelocity = 0;
	initialLifetime = 0;
	lifetime = 0;
	autofade = false;		
}

Particle::Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade) : Sprite(image)
{	
	velocityx = velx;
	velocityy = vely;
	angularVelocity = angularVel;
	initialLifetime = lifetime;
	this->lifetime = lifetime;
	this->autofade = autofade;	
}

double Particle::GetLifetime() const
{
	return lifetime;
}

void Particle::Update(double elapsed )
{
	Sprite::Update(elapsed);
	
	/*for (uint8 i = 0; i < lstAffectors.Size(); i++)
		if(lstAffectors[i]->IsCollide(this))	lstAffectors[i]->AffectParticle(this);*/
			

	SetX( GetX() + (velocityx * elapsed) );
	SetY( GetY() + (velocityy * elapsed) );
	SetAngle( GetAngle() + (angularVelocity * elapsed) );
	
	if (autofade)
		SetColor( GetRed(), GetGreen(), GetBlue(), (uint8)(lifetime * 255 / initialLifetime) );

	lifetime -= elapsed;

	if (lifetime < 0 ) lifetime = 0;
}