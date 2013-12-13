#ifndef UGINE_AFFECTOR_H
#define UGINE_AFFECTOR_H

#include "types.h"
#include "Particle.h"

class Affector
{
	public:
		Affector();
		Affector(double x1, double y1, double x2, double y2);
		void SetMinColor(uint8 r, uint8 g, uint8 b);
		void SetMaxColor(uint8 r, uint8 g, uint8 b);
		void SetAngularVelocity(double minVel, double maxVel);
		void AffectParticle (Particle* particle) const;
		bool IsCollide(Particle *particle) const;

	private:
		double x1, x2;
		double y1, y2;
		double minAngVel, maxAngVel;
		uint8 rmin,rmax;
		uint8 gmin,gmax;
		uint8 bmin,bmax;	
};

#endif