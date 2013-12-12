#include "image.h"
#include "Particle.h"

class Emitter
{
	public:
		Emitter(Image* image, bool autofade);

		virtual void SetPosition(double x, double y);
		virtual void SetX(double x);
		virtual void SetY(double y); 
		virtual double GetX() const;
		virtual double GetY()const;
		virtual void SetRate(double minrate, double maxrate);
		virtual void SetVelocityX(double minvelx, double maxvelx);
		virtual void SetVelocityY(double minvely, double maxvely);
		virtual void SetAngularVelocity(double minangvel, double maxangvel);
		virtual void SetLifetime(double minlifetime, double maxlifetime);
		virtual void SetMinColor(uint8 r, uint8 g, uint8 b);
		virtual void SetMaxColor(uint8 r, uint8 g, uint8 b);
		virtual void SetBlendMode(Renderer::BlendMode mode);
		virtual void Start();
		virtual void Stop();
		virtual bool IsEmitting() const;
		virtual void Update(double elapsed);
		virtual void Render() const;

	private:
		Image* image;
		bool autofade;
		double x, y;
		double minrate, maxrate;
		double minvelx, maxvelx;
		double minvely, maxvely;
		double minangvel, maxangvel;
		double minlifetime, maxlifetime;
		uint8 minr, ming, minb; 
		uint8 maxr, maxg, maxb;
		Renderer::BlendMode blendMode;
		bool emitting;
		
		Array<Particle> particles;
};