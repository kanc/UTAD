#include "../include/Emitter.h"

Emitter::Emitter(Image* image, bool autofade)
{
	this->image = image;
	this->autofade = autofade;
}

void Emitter::SetPosition(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Emitter::SetX(double x)
{
	this->x = x;
}

void Emitter::SetY(double y)
{
	this->y = y;
}

double Emitter::GetX() const
{
	return x;
}

double Emitter::GetY() const
{
	return y;
}

void Emitter::SetRate(double minrate, double maxrate)
{
	this->minrate = minrate;
	this->maxrate = maxrate;
}

void Emitter::SetVelocityX(double minvelx, double maxvelx)
{
	this->minvelx = minvelx;
	this->maxvelx = maxvelx;
}

void Emitter::SetVelocityY(double minvely, double maxvely)
{
	this->minvely = minvely;
	this->maxvely = maxvely;

}

void Emitter::SetAngularVelocity(double minangvel, double maxangvel)
{
	this->minangvel = minangvel;
	this->maxangvel = maxangvel;
}

void Emitter::SetLifetime(double minlifetime, double maxlifetime)
{
	this->minlifetime = minlifetime;
	this->maxlifetime = maxlifetime;
}

void Emitter::SetMinColor(uint8 r, uint8 g, uint8 b)
{
	minr = r;
	ming = g;
	minb = b;
}

void Emitter::SetMaxColor(uint8 r, uint8 g, uint8 b)
{
	maxr = r;
	maxg = g;
	maxb = b;
}

void Emitter::SetBlendMode(Renderer::BlendMode mode)
{
	blendMode = mode;
}

void Emitter::Start()
{
	emitting = true;
}

void Emitter::Stop()
{
	emitting = false;
}

bool Emitter::IsEmitting() const
{
	return emitting;
}

void Emitter::Update(double elapsed)
{

}

void Emitter::Render() const
{

}