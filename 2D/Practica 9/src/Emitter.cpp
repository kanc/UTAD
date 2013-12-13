#include "../include/Emitter.h"
#include "../include/math.h"


Emitter::Emitter(Image* image, bool autofade)
{
	this->image = image;
	this->autofade = autofade;
	blendMode = Renderer::ADDITIVE;
	emitting = false;
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
	/*

	if (emitting)
	{			
		double nParticles = (minrate + WrapValue(rand(),(uint32)maxrate - minrate)) * elapsed;		

		//añadimos al pool las particulas "muertas"
		for (uint32 i = 0; i < particles.Size(); i++)	
			if (particles[i]->GetLifetime() == 0)
				particlesPool.Add(i);

		double poolSize = particlesPool.Size();

		//reusamos las particulas del pool
		for (uint32 i = 0; i < poolSize; i++)		
			ReviveParticle(particles[particlesPool[i]]);

		particlesPool.Clear();

		//creamos las nuevas que necesitemos 
		for (uint32 i = 0; i < nParticles - poolSize; i++)		
			particles.Add(CreateParticle());

	}

	//actualizamos las particles
	for (uint32 i = 0; i < particles.Size(); i++)	
		particles[i]->Update(elapsed);		
	*/
	
	if ( emitting ) 
	{
		uint32 nParticles = (minrate + WrapValue(rand(),maxrate - minrate)) * elapsed;	
        for ( uint32 i = 0; i < nParticles; i++ ) 
            particles.Add(CreateParticle());        
	}
	
    Array<uint32> deleteParticles;
    for ( uint32 i = 0; i < particles.Size(); i++ ) 
	{
        particles[i]->Update(elapsed);
        if ( particles[i]->GetLifetime() <= 0 )
            deleteParticles.Add(i);
	}

	// Borramos las particulas que sea necesario
    for ( int i = deleteParticles.Size() - 1; i > 0; i-- ) {
        particles.RemoveAt(i);
    }
							
}

void Emitter::GenerateRandomProperties(double& velocityX, double& velocityY, double& angVel, double& lifetime, uint8& r, uint8& g, uint8& b) const
{
	velocityX = minvelx +  WrapValue(rand(), maxvelx - minvelx);
	velocityY = minvely + WrapValue(rand(), maxvely - minvely);
	angVel = minangvel + WrapValue(rand(), maxangvel - minangvel);
	lifetime = minlifetime + WrapValue(rand(), maxlifetime - minlifetime);
	r = minr + rand() % (maxr - minr + 1);
	g = ming + rand() % (maxg - ming + 1);
	b = minb + rand() % (maxb - minb + 1);
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