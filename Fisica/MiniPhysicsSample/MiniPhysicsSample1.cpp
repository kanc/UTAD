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
#include "vector.h"
#include "display.h"

//#############################################################################
//-----------------------------------------------------------------------------
const float SYM_EPSILON=0.001f;
const float delta_time=0.1f;
#define GRAVITY vmake(0.f, -10.0f)//.4f;
#define AIR_FRICTION .001f

struct Ball
{
  vec2   oldpos;
  vec2   pos;
  vec2   vel;
  GLuint gfx;
  float  radius;
  float  mass;
  vec2	 colDir;
};
#define NUM_BALLS 50//12
Ball balls[NUM_BALLS];
#define MAX_BALL_SPEED 2.f
#define JUMP_SPEED 100.0f//20.f
#define THRESHOLD_BRAKE_X 1.f
#define THRESHOLD_STOP_Y 1.f
#define THRESHOLD_STOP  (SYM_EPSILON*10000)
#define MIN_REACTIVATION_ENERGY 500.0f


bool collided[NUM_BALLS][NUM_BALLS+1];
bool deactivated[NUM_BALLS];
bool reactivated[NUM_BALLS];
//bool staticContact[NUM_BALLS];

//-----------------------------------------------------------------------------
// Uses the 1D formula:
//
//       v1*(m1-m2) + 2*m2*v2
// u1 = --------------------
//             m1 + m2
//
//       v2*(m2-m1) + 2*m1*v1
// u2 = --------------------
//             m1 + m2
//
// Where v1,v2 are the initial velocities and u1,u2 the end ones
//
void solve_collision(int i, int j, float rest)
{

 
  vec2 pos1 = balls[i].pos;
  float m1  = balls[i].mass;
  vec2 v1   = balls[i].vel;
  vec2 pos2 = balls[j].pos;
  float m2  = balls[j].mass;
  vec2 v2   = balls[j].vel;

  // Find collision axis
  vec2 e = vsub(pos2, pos1);
  float len=vlen(e);
  if( len < SYM_EPSILON )
  {
	  //ill-conditioned axis, replace for y axis
	  e=vmake(0,1); len=1;
  }
  else
  {e = vscale(e, 1.f/vlen(e));}

  if( deactivated[j])
  {
	  float imp = ( 1.0f + rest)*vdot(v1, e);
	  balls[i].vel=vadd(balls[i].vel, vscale(e, -imp));
  }
  else
  {  
	  // Find components
	  //float c1e = vdot(v1, e);
	  //vec2  v1e = vscale(e, c1e);
	  //vec2  v1t = vsub(v1, v1e);
	  //float c2e = vdot(v2, e);
	  //vec2  v2e = vscale(e, c2e);
	  //vec2  v2t = vsub(v2, v2e);
	  ////Solve 1-D part: (m1, c1e) and (m2, c2e)
	  //float u1e = (c1e * (m1 - m2) + (1.0f+rest) * m2 * c2e) / (m1 + m2);
	  //float u2e = (c2e * (m2 - m1) + (1.0f+rest) * m1 * c1e) / (m1 + m2);
  
	  //////Compose result vectors
	  //balls[i].vel = vadd( vscale(e, u1e), v1t);
   //   balls[j].vel = vadd( vscale(e, u2e), v2t);

	  //same but shorter and controlling momentum
	  float momentum = m1*vlen2(v1) + m2*vlen2(v2);
	  vec2 v21 = vsub(v2, v1); 
	  float v21n = vdot(v21, e);
	  if( v21n < -SYM_EPSILON)
	  {
		  float imp = -( 1.0f + rest)*m1*m2*v21n/(m1+m2);
		  vec2 impe=vscale(e,imp);
		  vec2 vi_new=vsub(balls[i].vel, vscale(impe,1.0f/m1));
		  vec2 vj_new=vadd(balls[j].vel, vscale(impe,1.0f/m2));
		  float momentum_new = m1*vlen2(vi_new) + m2*vlen2(vj_new);
		  balls[i].vel=vi_new;
		  balls[j].vel=vj_new;
		  assert( momentum_new <= momentum*1.2f );

	  }
	  else
	  {
		  assert( v21n > (-SYM_EPSILON));
	  }
	}
}
void solve_wallColisions()
{
	const float wall_rest=0.9f;//0.8f;
    for (int i = 0; i < NUM_BALLS; i++)
    {
	  if( deactivated[i])
	  {
		  continue;//deactivate objects cannot move
	  }

      // Rebound on sides
      if (balls[i].vel.x > 0.f)
      {
        if (balls[i].pos.x > SCR_WIDTH - balls[i].radius)
		{
          balls[i].vel.x *= -wall_rest;//-1.f;
		  balls[i].pos.x = SCR_WIDTH - balls[i].radius;
		}
      } else {
        if (balls[i].pos.x - balls[i].radius < 0)
		{
          balls[i].vel.x *= -wall_rest;//-1.f;
		  balls[i].pos.x = balls[i].radius;
		}
      }

      // If touching ground...
      if (balls[i].vel.y < 0.f &&(balls[i].pos.y - balls[i].radius) <= 0)
      {
        // Rebound
        if( reactivated[i])
			balls[i].vel.y = 0.0f;//-0.8f;
		else
			balls[i].vel.y *= -wall_rest;//-0.8f;

        balls[i].pos.y = balls[i].radius; // This causes re-interpenetration, and sometimes great instability!

        // Stop nearly stopped balls at the ground
		if (vlen2(balls[i].vel) < THRESHOLD_STOP)
        {
          balls[i].vel.y = 0.f;
          balls[i].vel.x = 0.f;
		  deactivated[i]=true;
        }
	  }

	  //ceil
      if (balls[i].vel.y > 0.f &&(balls[i].pos.y + balls[i].radius) > SCR_HEIGHT)
      {
        // Rebound
        balls[i].vel.y *= -wall_rest;//-0.8f;

        // Stop nearly stopped balls at the ground
	/*	if (vlen2(balls[i].vel) < THRESHOLD_STOP)
        {
          balls[i].vel.y = 0.f;
          balls[i].vel.x = 0.f;
        }*/
	  }
	  
	}

}

float getMaxMomentun()
{
	float maxMomentum=0;
	for (int i = 0; i < NUM_BALLS; i++)
    {
//	    float m1  = balls[i].mass;
	    vec2 v1   = balls[i].vel;

		float m=vlen2(v1);
		if( m > maxMomentum)maxMomentum=m;
	}

	return maxMomentum;
}

float getEnergy()
{
	float energy=0;
	for (int i = 0; i < NUM_BALLS; i++)
    {
	    float m1  = balls[i].mass;
	    vec2 v1   = balls[i].vel;

		energy+=m1*vlen2(v1);
	}
	energy*=.5f;

	return energy;
}

void dumpSystem( float factor)
{
	for (int i = 0; i < NUM_BALLS; i++)
    {
	    balls[i].vel.x*=factor;
	    balls[i].vel.y*=factor;
	}
}

bool isCollisionSolved(int i, int j)
{
  vec2 pos1 = balls[i].pos;
  vec2 pos2 = balls[j].pos;
  vec2 v1   = balls[i].vel; 
  vec2 v2   = balls[j].vel;
  vec2 e = vsub(pos2, pos1);
  float len=vlen(e);
  if( len < SYM_EPSILON )
  {
	  //ill-conditioned axis, replace for y axis
	  e=vmake(0,1); len=1;
  }
  else
  {e = vscale(e, 1.f/vlen(e));}

	vec2 v21 = vsub(v2, v1); 
	float v21n = vdot(v21, e);
	if( v21n < -SYM_EPSILON)
	{
		return false;
	}

	return true;
}
void move(int i)
{
    balls[i].oldpos = balls[i].pos;
	//add forces(gravity)
	{
		balls[i].vel = vadd(balls[i].vel, vscale(GRAVITY,delta_time));
		balls[i].vel = vscale(balls[i].vel, (1.f - AIR_FRICTION));
	}
	//process contacts
//    if (collided[i][NUM_BALLS])
//    {
	//for (int j = (i+1); j < NUM_BALLS; j++)
	//{
	//	if( collided[i][j] && !isCollisionSolved(i,j))
	//	{
	//		solve_collision(i, j,0.0);
	//	}
	//}
	// }
	// incorrect deactivation
	//if (vlen2(balls[i].vel) < THRESHOLD_STOP)
	//{
	//	deactivated[i]=true;
	//	return;
	//}

	//integrate velocity
    balls[i].pos = vadd(balls[i].oldpos, vscale(balls[i].vel,delta_time));
}
bool checkCollide(int i)
{
      for (int j = 0; j < NUM_BALLS; j++)
	  {
		if (i != j)// && collided[j][i] == false)
        {
          float limit = (balls[i].radius + balls[j].radius) * (balls[i].radius + balls[j].radius);
		  limit+=SYM_EPSILON;
		  if( vlen2(vsub(balls[i].pos, balls[j].pos)) <= limit)
		  {
			  //balls are colliding
			if ( vlen2(vsub(balls[i].oldpos, balls[j].pos)) > limit ||
				vlen2(vsub(balls[i].pos, balls[j].oldpos)) > limit)
			{	
			//balls are aproaching =>colliison
				collided[i][NUM_BALLS] = true;
				collided[i][j] = true;
			}
//			else
			//{
			////ball are posibly in static contact so just in case dump!
			//	solve_collision(i, j,0.0);
			//}
		  }
        }
	  }

	return collided[i][NUM_BALLS];
}
void processCollisions(int i)
{
	const float restitution=0.9f;

	balls[i].pos = balls[i].oldpos;
	for (int j = 0; j < NUM_BALLS; j++)
	{
		if( collided[i][j] && !collided[j][i])
		{
			// Rebound against the other ball! (but only once)
			if( deactivated[j])
			{
				float energy=.5f*balls[i].mass*vlen2(balls[i].vel);

				if( energy > MIN_REACTIVATION_ENERGY)
				{
//					staticContact[j]=false;
					deactivated[j]=false;
					reactivated[j]=true;
					if( reactivated[j])
					{
						solve_collision(i, j,0.3f);
					}
					else
					{
						solve_collision(i, j,restitution);
					}
				}
				else
				{
					//contact
	   	//		    vec2 colDir = vsub( balls[i].pos,balls[j].pos);
					//float len = vlen(colDir);
					//colDir.x/=len;colDir.y/=len;
					//if( colDir.y > 0.9f)
					{	
//						balls[i].vel.y = 0.0f;//vmake(0.0,0.0);
//						staticContact[i]=true;
					}
					solve_collision(i, j, 0.3f);
				}
				//cascade deactivation
				if (vlen2(balls[i].vel) < THRESHOLD_STOP)
				{
						balls[i].vel = vmake(0.0,0.0);
						deactivated[i]=true;
						break;
				}
			}
			else
			{
				if( reactivated[i] || reactivated[j])
				{
					solve_collision(i, j,0.3f);
				}
				else
				{
					solve_collision(i, j,restitution);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
int Main(void)
{
  // Load resources
  GLuint texbkg        = CORE_LoadBmp("data/circle-bkg-128.32.bmp"   , true);
  GLuint texlargeball  = CORE_LoadBmp("data/ball128.32.bmp"          , false);
  GLuint texsmallball  = CORE_LoadBmp("data/tyrian_ball.32.bmp"      , false);
  
  // Init game state
  for (int i = 0; i < NUM_BALLS; i++)
  {
    float radius;
    if ( CORE_FRand(0.f, 1.f) < 0.1f)
    {
      radius = 48.f;
      balls[i].radius = radius;
      balls[i].mass = 10.f;
      balls[i].gfx = texlargeball;
	  balls[i].colDir= vmake(0.0f, 0.0f);
    }
    else
    {
      radius = 16.f;
      balls[i].radius = radius;
      balls[i].mass = 1.f;
      balls[i].gfx = texsmallball;
	  balls[i].colDir= vmake(0.0f, 0.0f);
    }
    balls[i].pos = vmake(CORE_FRand(radius, SCR_WIDTH-radius), CORE_FRand(radius, SCR_HEIGHT-radius));
//    balls[i].vel = vmake(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
    balls[i].vel = vmake(0, 10.0f);
  }

  // Set up rendering
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
  glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  memset(deactivated, 0, sizeof(deactivated));//reset deactivated
  memset(reactivated, 0, sizeof(reactivated));//reset deactivated
  while (!SYS_GottaQuit())
  {
    // Render
    glClear( GL_COLOR_BUFFER_BIT );

    // Render backgground
    for (int i = 0; i < 7; i++)
      for (int j = 0; j < 5; j++)
        CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f), vmake(128.f, 128.f), texbkg);

    // Render balls
    for (int i = 0; i < NUM_BALLS; i++)
      //if (i == 6)
      CORE_RenderCenteredSprite(balls[i].pos, vmake(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);

    SYS_Show();
#ifdef _DEBUG
	float energy=getEnergy();
	float momentum = getMaxMomentun();

#endif
    // Run balls and intercollisons
    memset(collided, 0, sizeof(collided));
    for (int i = 0; i < NUM_BALLS; i++)
    {
      // Move
	  if( deactivated[i])
	  {
		  continue;//deactivate objects cannot move
	  }

	   move(i);

      if(checkCollide(i))
      {
		processCollisions( i);
      }
	}
	//collision with walls
	solve_wallColisions();

#ifdef _DEBUG
	float new_energy=getEnergy();

	//while( new_energy > energy*1.3f)
	//{	
	//	dumpSystem(0.9f);
	//	new_energy=getEnergy();
	//}
//	float newMomentum = getMaxMomentun();

//	assert(new_energy <= (energy*10.0f));
//	assert(newMomentum <= momentum*2.0f );

#endif

    // Keypress!
    if (SYS_KeyPressed('I'))
    {
		//start single ball at random
		float radius=16.f;
		GLuint texBall=texsmallball;
		float mass=1.0f;
		int index=(int)CORE_FRand(0, NUM_BALLS-1);
		memset(collided, 0, sizeof(collided));

		if( balls[index].mass > 1.0)
		{
			radius=48.f;
			texBall=texlargeball;
			mass=10.0f;
		}
		balls[index].mass = mass;
		balls[index].gfx = texBall;
		balls[index].radius = radius;
	    balls[index].pos = vmake(CORE_FRand(radius, SCR_WIDTH-radius), CORE_FRand(SCR_HEIGHT*.5f, SCR_HEIGHT-radius));
//		balls[index].vel = vmake(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
		balls[index].vel = vmake(0, 10);
		deactivated[index]=false;
	}
    if (SYS_KeyPressed(' '))
    {
		//give an impulse to all balss

	  memset(deactivated, 0, sizeof(deactivated));
	  memset(reactivated, 0, sizeof(reactivated));
	  memset(collided, 0, sizeof(collided));

      for (int i = 0; i < NUM_BALLS; i++)
	  {
//        if (balls[i].pos.y - balls[i].radius < 5.f)
//        {
          if (fabs(balls[i].vel.x) < 0.1f)
            balls[i].vel.x = CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED);
          balls[i].vel.y = CORE_FRand(0, JUMP_SPEED);
//        }
	  }
    }
    if (SYS_KeyPressed(VK_CONTROL))
    {
	  //reset all
		glClear( GL_COLOR_BUFFER_BIT );

	  memset(deactivated, 0, sizeof(deactivated));
	  memset(reactivated, 0, sizeof(reactivated));
	  memset(collided, 0, sizeof(collided));

      for (int i = 0; i < NUM_BALLS; i++)
	  {
		float radius=balls[i].radius;
		balls[i].pos = vmake(CORE_FRand(radius, SCR_WIDTH-radius), CORE_FRand(radius, SCR_HEIGHT-radius));
//		balls[i].vel = vmake(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
		balls[i].vel = vmake(0, 10);
	  }
	  SYS_Show();
	}
    // Keep system running
    SYS_Pump();
    SYS_Sleep(17);
  }

  CORE_UnloadBmp(texbkg);
  CORE_UnloadBmp(texlargeball);
  CORE_UnloadBmp(texsmallball);

  return 0;
}