#include "../include/Emitter.h"
#include "../include/math.h"
#include "../include/screen.h"


Emitter::Emitter(Image* image, bool autofade)
{
	this->image = image;
	this->autofade = autofade;
	blendMode = Renderer::ADDITIVE;
	emitting = false;	
}

Emitter::~Emitter()
{	
	for (int i = 0; i < particles.Size(); i++)
		delete particles[i];

	particles.Clear();
}


void Emitter::Update(double elapsed)
{	
	Array<int> deleteParticles;

	if (emitting) 
	{
		int nParticles = (minrate + (maxrate - minrate) * (float)rand() / RAND_MAX) * elapsed;	
        for (int i = 0; i < nParticles; i++) 
            particles.Add(CreateParticle());        
	}	    

    for (int i = 0; i < particles.Size(); i++) 
	{
		particles[i]->Update(elapsed);

		for (uint8 a = 0; a < affectors.Size(); a++)
			if (affectors[a]->IsCollide(particles[i])) affectors[a]->AffectParticle(particles[i]);

        if ( particles[i]->GetLifetime() <= 0 )
            deleteParticles.Add(i);
	}

    for (int i = 0; i < deleteParticles.Size(); i++ ) 
    {    		
		for (uint8 a = 0; a < affectors.Size(); a++)
			affectors[a]->DeleteAffectedParticle(particles[i]);

		particles.RemoveAt(i);
	}
							
}

void Emitter::GenerateRandomProperties(double& velocityX, double& velocityY, double& angVel, double& lifetime, uint8& r, uint8& g, uint8& b) const
{
	velocityX = minvelx + (maxvelx - minvelx) * (float)rand() / RAND_MAX;
	velocityY = minvely + (maxvely - minvely) * (float)rand() / RAND_MAX;
	angVel = minangvel + (maxangvel - minangvel) * (float)rand() / RAND_MAX;
	lifetime = minlifetime +  (maxlifetime - minlifetime) * (float)rand() / RAND_MAX;
	r = minr + (maxr - minr) * (float)rand() / RAND_MAX;
	g = ming + (maxg - ming) * (float)rand() / RAND_MAX;
	b = minb + (maxb - minb) * (float)rand() / RAND_MAX;

}

void Emitter::ReviveParticle(Particle* particle) const
{
	double velx, vely, angVel, lifetime;
	uint8 r, g, b;

	GenerateRandomProperties(velx, vely, angVel, lifetime, r, g, b);

	particle->SetVelX(velx);
	particle->SetVelY(vely);
	particle->SetAngularVel(angVel);
	particle->SetLifetime(lifetime);
	particle->SetX(x);
	particle->SetY(y);
	particle->SetColor(r,g,b,255);

}

Particle * Emitter::CreateParticle() const
{
	double velx, vely, angVel, lifetime;
	uint8 r, g, b;

	GenerateRandomProperties(velx, vely, angVel, lifetime, r, g, b);

	Particle* newParticle = new Particle(image, velx, vely,angVel,lifetime,autofade);
	
	newParticle->SetX(x);
	newParticle->SetY(y);
	newParticle->SetBlendMode(blendMode);
	newParticle->SetColor(r,g,b,255);

	return newParticle;
}

void Emitter::Render() const
{
	for (uint32 i = 0; i < particles.Size(); i++)
	{
		if (particles[i]->GetLifetime())
			particles[i]->Render();
	}

}

void Emitter::AddAffector(Affector* affector)
{
	if (affector)
		affectors.Add(affector);
}

void Emitter::DeleteAffector(Affector *affector)
{
	for (uint8 i = 0; i < affectors.Size(); i++)
		if (affectors[i] == affector)
		{	
			affectors.RemoveAt(i);
			break;
		}
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