#include "../include/Emitter.h"


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
	//actualizamos y metemos en el pool de particulas las que han muerto
	for (uint32 i = 0; i < particles.Size(); i++)	
	{	particles[i]->Update(elapsed);

		if (particles[i]->GetLifetime() == 0)
			particlesPool.Add(particles[i]);
	}
	srand(time_t(100));

	if (emitting)
	{		
		double nParticles = (minrate + (rand() % (uint32)maxrate)) * elapsed;

		double poolSize = particlesPool.Size();

		//reusamos las particulas del pool
		for (uint32 i = 0; i < poolSize; i++)		
			ReviveParticle(particlesPool[i]);

		//borramos las particulas del pool
		for (uint32 i = 0; i < poolSize; i++)
			particlesPool.RemoveLast();

		//creamos las nuevas que necesitemos 
		for (uint32 i = 0; i < nParticles - poolSize; i++)		
			particles.Add(CreateParticle());

	}
							
}

void Emitter::GenerateRandomProperties(double& velocityX, double& velocityY, double& angVel, double& lifetime, uint8& r, uint8& g, uint8& b) const
{
	velocityX = minvelx + rand() % (uint32)maxvelx;
	velocityY = minvely + rand() % (uint32)maxvely;
	angVel = minangvel + rand() % (uint32)maxangvel;
	lifetime = minlifetime + rand() % (uint32)maxlifetime;
	r = minr + rand() % (uint32)maxr;
	g = ming + rand() % (uint32)maxg;
	b = minb + rand() % (uint32)maxb;
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