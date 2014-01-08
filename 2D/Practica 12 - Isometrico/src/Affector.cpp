#include "../include/Affector.h"

Affector::Affector()
{

}

Affector::Affector(double x1, double y1, double x2, double y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void Affector::SetMinColor(uint8 r, uint8 g, uint8 b)
{
	rmin = r;
	gmin = g;
	bmin = b;
}

void Affector::SetMaxColor(uint8 r, uint8 g, uint8 b)
{
	rmax = r;
	gmax = g;
	bmax = b;
}

void Affector::SetAngularVelocity(double minVel, double maxVel)
{
	minAngVel = minVel;
	maxAngVel = maxVel;
}

void Affector::AffectParticle (Particle* particle) 
{	
	bool affected = false;

	for (uint32 i = 0; i < affectedParticles.Size(); i++)
	{	if (affectedParticles[i] == particle)
		{
			affected =true;
			break;
		}
	}

	if (!affected)
	{	double angVel = minAngVel + (maxAngVel - minAngVel) * (float)rand() / RAND_MAX;	
		double r = rmin + (rmax - rmin) * (float)rand() / RAND_MAX;
		double g = rmin + (gmax - gmin) * (float)rand() / RAND_MAX;
		double b = rmin + (bmax - bmin) * (float)rand() / RAND_MAX;

		particle->SetAngularVel(angVel);
		particle->SetColor(r,g,b,particle->GetAlpha());

		affectedParticles.Add(particle);
	}	


}

bool Affector::IsCollide(Particle * particle) const
{
	bool collide = false;

	//if (particle->GetX() + particle->GetImage()->GetWidth() < x1 || x1 + (x2-x1) < particle->GetX() || particle->GetY() + particle->GetImage()->GetHeight() < y1 || y1 + (y2-y1) < particle->GetY())
	
	if (particle->GetX() > x1 && particle->GetX() < x2 && particle->GetY() > y1 && particle->GetY() < y2)
		collide = true;

	return collide;
}

void Affector::DeleteAffectedParticle(Particle* particle)
{
	for (uint32 i = 0; i < affectedParticles.Size(); i++)
		if (affectedParticles[i] == particle)
		{	
			affectedParticles.RemoveAt(i);
			break;
		}
}