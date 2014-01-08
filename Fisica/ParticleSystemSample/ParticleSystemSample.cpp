#pragma pack(1)
#pragma warning(disable:4996) // Using open/close/read... for file access

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <GL/glu.h>

#include <io.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>
#include "ParticleSystemSample.h"
#include "display.h"
//-----------------------------------------------------------------------------

//#############################################################################
//-----------------------------------------------------------------------------
const float FPS=60;
const int substep=5;
const float SYM_EPSILON=0.001f;
const float delta_time=0.1f;
#define GRAVITY vmake(0.f, -1000.0f)//.4f;
#define AIR_FRICTION .001f
#define TICKS_PER_SECOND 1000;

#define MAX_PARTICLES 50
tParticlePool particlePool;
tEmitter* myEmmiter;
const float min_radius = 20.0f;

#define MAX_BALL_SPEED 20.f
#define JUMP_SPEED 100.0f//20.f
//#define THRESHOLD_STOP  (SYM_EPSILON*1000)
GLuint texsmallball;
GLuint texcursor;
tCursor* cursor;
float atractorScale=10.0;///10.0f;
//float gravityForce = GRAVITY;// -1000.0f;
//-----------------------------------------------------------------------------
bool initParticlePool(int size)
{
	particlePool.head = new tParticle();
	particlePool.head->index=0;
//	particlePool.head->prev=NULL;
	tParticle* prev= particlePool.head;
//	tParticle* current = particlePool.head->next;
	for( int i=1; i < size; i++)
	{
		tParticle* current = new tParticle();
		current->index=i;
		prev->next = current;
//		particlePool.current->prev=prev;
		prev = current;
//		current=particlePool.current->next;
	}
//	particlePool.current=particlePool.head->next;

	return true;
}
void destroyParticlePool()
{
//  particlePool.current = particlePool.head;
	tParticle* current = particlePool.head;
  while( current)
  {
//	  tParticle* current=particlePool.current;
	  tParticle* prev=current;
	  current=current->next;
	  delete prev;
  }

}

bool initEmmiter()
{
	myEmmiter = new tEmitter;
	strcpy(myEmmiter->name,"emmiter1");
	myEmmiter->id=0x0001;
	myEmmiter->flags=0;
	myEmmiter->prev=0;myEmmiter->next=0;

	myEmmiter->pos = vmake(SCR_WIDTH*.5f, SCR_HEIGHT*.3f);
	myEmmiter->vel = vmake(10.0,10.0);
	myEmmiter->speedVar = 10.0f;
	myEmmiter->particle=0;
	myEmmiter->maxParticles= MAX_PARTICLES;
	myEmmiter->particleCount=0;
	myEmmiter->emitsPerFrame = 1;//NUM_PARTICLES/10;
	myEmmiter->emitVar = 10;//NUM_PARTICLES/10;
	myEmmiter->life = 1000;
	myEmmiter->lifeVar = 50;
	myEmmiter->forces = vmake(0.0,0.0);

	return true;
}
void destroyEmmmiter(tEmitter *emitter)
{
	//devuelve particulas al pool
	tParticle *particle = emitter->particle;
	while( particle!=NULL)
	{
		if (particle->prev != NULL)
			particle->prev->next = particle->next;
		else
			emitter->particle = particle->next;
		if (particle->next != NULL) particle->next->prev = particle->prev;

		//devuelve la particula al pool
		particle->next = particlePool.head->next;
		particle->prev = particlePool.head;
		particlePool.head->next = particle;
		particle = emitter->particle;
		emitter->particleCount--;
	}
	delete emitter;
}

bool addParticle(tEmitter *emitter)
{
	tParticle *particle;
	if (emitter != NULL && particlePool.head->next != NULL &&
	emitter->particleCount < emitter->maxParticles) {
		particle = particlePool.head->next; 
		//saca la particual del pool
		particlePool.head->next=particle->next;
		if (particle->next != NULL) particle->next->prev = particle->prev;
		//enlaza la particula en el emisor
		if (emitter->particle != NULL) emitter->particle->prev = particle;
		particle->next = emitter->particle;
		particle->prev = NULL;
		emitter->particle = particle;
		particle->radius = min_radius;
		particle->pos= emitter->pos;
		particle->prevPos= emitter->pos;
		particle->vel.x = emitter->vel.x*(1+emitter->speedVar * CORE_FRand(-1,1));
		particle->vel.y = emitter->vel.y*(1+emitter->speedVar * CORE_FRand(0,1));
		particle->index = texsmallball;
//		particle->color = tColor(1,1,1);//RGB color
		particle->life=emitter->life + (int)((float)emitter->lifeVar* CORE_FRand(0,1));
		particle->mass=1.0f+(int)((float)emitter->lifeVar* CORE_FRand(0,1));
//		particle->deltaColor = 1.0/ particle->life;
		emitter->particleCount++;
		return true;
	}
	return false;
}

bool updateParticle(tParticle *particle,tEmitter *emitter, float dt)
{
	if (particle == NULL)return false;

	if (particle->life > 0)
	{
		for(int i=0; i < substep; i++)
		{
			particle->prevPos = particle->pos;
			tVector dir = vsub(cursor->pos,particle->pos); 
			tVector forces = vscale(dir,atractorScale);
//			tVector forces = vmake(0,0);
			forces=vadd(emitter->forces,forces);
			tVector incv = vscale(forces, 1.0f/particle->mass);
			particle->vel = vadd(particle->vel, vscale(incv,dt));
			particle->pos = vadd(particle->pos, vscale(particle->vel,dt));
		}
		//particle->prevColor = particle->color;
		//particle->color += particle->deltaColor;
		particle->radius = max(4.0f,((float)particle->life/(float)myEmmiter->life)*min_radius);
		particle->life--;
	}
	else//(particle->life == 0)
	{ //... si la partícula ha muerto eliminarla y devolverla al grupo de partículas
		if (particle->prev != NULL)
			particle->prev->next = particle->next;
		else
			emitter->particle = particle->next;
		if (particle->next != NULL) particle->next->prev = particle->prev;

		//devuelve la particula al pool
		particle->next = particlePool.head->next;
		if( particlePool.head->next!=NULL)particlePool.head->next->prev = particle;
		particle->prev = particlePool.head;
		particlePool.head->next = particle;
		emitter->particleCount--;
	}
	return true;
}


bool updateEmitter(tEmitter *emitter, tVector forces, float dt)
{
	int loop,emits;
	tParticle *particle, *next;
	if (emitter != NULL)
	{
		emitter->forces=forces;
		if (emitter->particle != NULL)
		{
			particle = emitter->particle;
			while (particle)
			{
				next = particle->next;
				updateParticle(particle,emitter,dt);
				particle = next;
			}
		}
		emits=emitter->emitsPerFrame+(int)((float)emitter->emitVar*CORE_FRand(0,1));
		for (loop = 0; loop < emits; loop++)
			addParticle(emitter);
		return TRUE;
	}
	return FALSE;
}
void renderParticles(tEmitter *emitter)
{
	if (emitter->particle != NULL)
	{
		tParticle* particle = emitter->particle;
		while (particle)
		{
			CORE_RenderCenteredSprite(particle->pos, 
				vmake(particle->radius , particle->radius ), particle->index);
			particle = particle->next;
		}
	}
}

void applyDeflectors(tEmitter *emitter)
{
	float wall_rest=0.9f;//0.8f;

	if (emitter->particle != NULL)
	{
		tParticle* particle = emitter->particle;
		while (particle)
		{
			//collisions with sides
			if (particle->vel.x > 0.f)
			{
				if (particle->pos.x > SCR_WIDTH - particle->radius)
				{
					particle->vel.x *= -wall_rest;//-1.f;
					particle->pos.x = SCR_WIDTH - particle->radius;
				}
			} else {
				if (particle->pos.x - particle->radius < 0)
				{
					particle->vel.x *= -wall_rest;//-1.f;
					particle->pos.x = particle->radius;
				}
			}
		  // If touching ground...
		  if (particle->vel.y < 0.f &&( particle->pos.y - particle->radius) < 0)
		  {
			// Rebound
			particle->vel.y *= -wall_rest;//-0.8f;
			particle->pos.y = particle->radius; // This causes re-interpenetration, and sometimes great instability!

		  }

		  // bouncing with ceil
		  if (particle->vel.y > 0.f &&(particle->pos.y + particle->radius) > SCR_HEIGHT)
		  {
			// Rebound
			particle->vel.y *= -wall_rest;//-0.8f;
		  }

			particle = particle->next;
		}
	}

}

void initCursor()
{
	cursor = new tCursor;

	if( cursor)
	{
		cursor->pos= vmake(SCR_WIDTH*.7f, SCR_HEIGHT*.7f);
		cursor->radius=100.0;
		cursor->index = texcursor;
	}
}

void destroyCursor()
{
	delete cursor;
}

int Main(void)
{
  // Load resources
  texsmallball  = CORE_LoadBmp("data/tyrian_ball.32.bmp"      , false);
  texcursor  = CORE_LoadBmp("data/cursor.bmp", false);
  
  initCursor();

  initParticlePool(MAX_PARTICLES);

  initEmmiter();

  // Set up rendering
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
  glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  DWORD start_tick= GetTickCount();

  while (!SYS_GottaQuit())
  {
    // Render
    glClear( GL_COLOR_BUFFER_BIT );
		
	CORE_RenderCenteredSprite(cursor->pos, 
				vmake(cursor->radius , cursor->radius ), cursor->index);

	//fixed substep
	float dt =1.0f/(substep*FPS);
	//add gravity
//	tVector emitterforces=vmake(0.0f,0.0f);
	tVector emitterforces= GRAVITY; //vmake(0,gravityForce);

	updateEmitter( myEmmiter, emitterforces, dt);

	applyDeflectors(myEmmiter);

	renderParticles(myEmmiter);

	SYS_Show();

	start_tick= GetTickCount();
    // Keypress!
	const float scale=2.0f;
    if (SYS_KeyPressed('O'))
    {
		if(cursor)cursor->pos.x-=1.0f*scale;
	}
    if (SYS_KeyPressed('P'))
    {
		if(cursor)cursor->pos.x+=1.0f*scale;
	}
    if (SYS_KeyPressed('Q'))
    {
		if(cursor)cursor->pos.y+=1.0f*scale;
	}
    if (SYS_KeyPressed('A'))
    {
		if(cursor)cursor->pos.y-=1.0f*scale;
	}
    if (SYS_KeyPressed('S'))
    {
		atractorScale*=1.1f;
		if( atractorScale > 1000.0f)atractorScale=1000.0f;
	}
    if (SYS_KeyPressed('W'))
    {
		atractorScale*=0.9f;
	}

    // Keep system running
    SYS_Pump();
    SYS_Sleep(17);
  }

  CORE_UnloadBmp(texsmallball);
  CORE_UnloadBmp(texcursor);

  destroyEmmmiter(myEmmiter);
  destroyParticlePool();
  destroyCursor();

  return 0;
}