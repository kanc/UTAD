#include "../include/Particle.h"
#include "../include/sprite.h"

Particle::Particle()
{
	
}

Particle::Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade)
{
	image->SetMidHandle();
	SetImage(image);

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

void Particle::Update(double elapsed)
{
	SetX( GetX() + (velocityx * elapsed) );
	SetY( GetY() + (velocityy * elapsed) );
	SetAngle( GetAngle() + (angularVelocity * elapsed) );
	
	if (autofade)
		SetColor( GetRed(), GetGreen(), GetBlue(), (uint8)(lifetime * 255 / initialLifetime) );

	lifetime -= elapsed;

	if (lifetime < 0 ) lifetime = 0;
}