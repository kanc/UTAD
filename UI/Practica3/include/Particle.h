#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H

#include "sprite.h"
#include "image.h"


class Particle : public Sprite
{
	public:
		Particle();
		Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade);

		virtual double GetLifetime() const;
		virtual void SetLifetime(double lifet) { initialLifetime = lifet; lifetime = lifet; }
		virtual void SetVelX(double velx) { velocityx = velx; }
		virtual void SetVelY(double vely) { velocityy = vely; }
		virtual void SetAngularVel(double angVel) { angularVelocity = angVel; }
		virtual void SetAutoFade(bool autof) { autofade = autof; }
		virtual void Update(double elapsed );

	private:
		double velocityx, velocityy;
		double angularVelocity;
		double lifetime;
		double initialLifetime;
		bool autofade;
};

#endif