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


//-----------------------------------------------------------------------------
int Main(void);

//-----------------------------------------------------------------------------
#define SCR_WIDTH  640
#define SCR_HEIGHT 480
#define SCR_FULLSCREEN 0

//#############################################################################
HINSTANCE WIN_hInst      = 0;
int       WIN_nCmdShow   = 0;
HWND      WIN_hWnd       = 0;
HDC       WIN_hDC        = 0;
HGLRC     WIN_hGLRC      = 0;
bool      WIN_bGottaQuit = false;

//-----------------------------------------------------------------------------
LRESULT CALLBACK WIN_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
    case WM_PAINT:   hdc = BeginPaint(hWnd, &ps); EndPaint(hWnd, &ps); break;
    case WM_DESTROY: PostQuitMessage(0); break;
    default:         return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//-----------------------------------------------------------------------------
ATOM WIN_RegisterClass()
{
  WNDCLASS wc;

  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = WIN_WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = WIN_hInst;
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = "WIN_WindowClass";

  return RegisterClass(&wc);
}

//-----------------------------------------------------------------------------
bool WIN_InitInstance()
{
  RECT r; r.left = 0; r.right = SCR_WIDTH; r.top = 0; r.bottom = SCR_HEIGHT;
  AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
  WIN_hWnd = CreateWindow("WIN_WindowClass", "Demo Window", WS_OVERLAPPEDWINDOW,
          0, 0, r.right-r.left, r.bottom-r.top, NULL, NULL, WIN_hInst, NULL);

  if (!WIN_hWnd)
     return false;

  ShowWindow(WIN_hWnd, WIN_nCmdShow);
  UpdateWindow(WIN_hWnd);

  return true;
}

//-----------------------------------------------------------------------------
void WIN_EnableOpenGL()
{
  PIXELFORMATDESCRIPTOR pfd;
  int format;

  WIN_hDC = GetDC( WIN_hWnd );

  // Set the pixel format for the DC
  ZeroMemory( &pfd, sizeof( pfd ) );
  pfd.nSize = sizeof( pfd );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  format = ChoosePixelFormat( WIN_hDC, &pfd );
  SetPixelFormat( WIN_hDC, format, &pfd );

  // Create and enable the render context (RC)
  WIN_hGLRC = wglCreateContext( WIN_hDC );
  wglMakeCurrent( WIN_hDC, WIN_hGLRC );
}

//-----------------------------------------------------------------------------
void WIN_DisableOpenGL()
{
  wglMakeCurrent( NULL, NULL );
  wglDeleteContext( WIN_hGLRC );
  ReleaseDC( WIN_hWnd, WIN_hDC );
}

//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hI, HINSTANCE hPrevI, LPSTR lpCmdLine, int nCS)
{
  WIN_hInst    = hI;
  WIN_nCmdShow = nCS;
  if (!WIN_RegisterClass()) return -1;
  if (!WIN_InitInstance ()) return -1;
  WIN_EnableOpenGL();
  int retval = Main();
  WIN_DisableOpenGL();
  return retval;
}

//-----------------------------------------------------------------------------
void SYS_Pump()
{
  MSG msg;

  // Process messages if there are any
  while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )  )
  {
    if (msg.message == WM_QUIT)
      WIN_bGottaQuit = true;
    else
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

//-----------------------------------------------------------------------------
void SYS_Show()
{
  glFlush();
  SwapBuffers( WIN_hDC );
}

//-----------------------------------------------------------------------------
bool SYS_GottaQuit()
{
  return WIN_bGottaQuit;
}

//-----------------------------------------------------------------------------
#define SYS_KEY_UP    VK_UP
#define SYS_KEY_DOWN  VK_DOWN
#define SYS_KEY_LEFT  VK_LEFT
#define SYS_KEY_RIGHT VK_RIGHT

bool SYS_KeyPressed(int key)
{
  return (GetAsyncKeyState(key) & 0x8000) != 0;
}

//-----------------------------------------------------------------------------
void SYS_Sleep(int ms)
{
  Sleep(ms);
}
//
//#############################################################################

typedef unsigned       char byte;
typedef unsigned short int  word;
typedef unsigned       int  dword;

struct CORE_BMPFileHeader
{
  byte  mark[2];
  byte  filesize[4];
  byte  reserved[4];
  byte  pixdataoffset[4];

  byte  hdrsize[4];
  byte  width[4];
  byte  height[4];
  byte  colorplanes[2];
  byte  bpp[2];
  byte  compression[4];
  byte  pixdatasize[4];
  byte  hres[4];
  byte  vres[4];
  byte  numcol[4];
  byte  numimportantcolors[4];
};

#define READ_LE_DWORD(a) (a[0] + a[1]*0x100 + a[2]*0x10000 + a[3]*0x1000000)

//-----------------------------------------------------------------------------
GLuint CORE_LoadBmp(const char filename[], bool wrap)
{
  GLint              retval = -1;
  CORE_BMPFileHeader hdr;
  byte               pixels[256 * 256 * 4];
  
  int fd = open(filename, O_RDONLY);
  if (fd != -1)
  {
    read(fd, &hdr, sizeof(hdr));

    if (hdr.mark[0] == 'B' && hdr.mark[1] == 'M')
    {
      dword offset = READ_LE_DWORD(hdr.pixdataoffset);
      lseek(fd, offset, SEEK_SET);
      read(fd, pixels, sizeof(pixels));

      dword width = READ_LE_DWORD(hdr.width);
      dword height = READ_LE_DWORD(hdr.height);

      GLuint texid = 1;

      glGenTextures( 1, &texid );
      glBindTexture( GL_TEXTURE_2D, texid );
      glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );

      glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);

      retval = texid;
    }
    close(fd);
  }

  return retval;
}

void CORE_UnloadBmp(GLuint texid)
{
  glDeleteTextures( 1, &texid );
}

float CORE_FRand(float from, float to)
{
  return from + (to-from)*(rand()/(float)RAND_MAX);
}

//-----------------------------------------------------------------------------
struct vec2 { float x, y; };
inline vec2  vmake (float x, float y) { vec2 r; r.x = x; r.y = y; return r; }
inline vec2  vadd  (vec2 v1, vec2 v2) { return vmake(v1.x + v2.x, v1.y + v2.y); }
inline vec2  vsub  (vec2 v1, vec2 v2) { return vmake(v1.x - v2.x, v1.y - v2.y); }
inline vec2  vscale(vec2 v, float f)  { return vmake(v.x * f, v.y * f); }
inline float vlen2 (vec2 v)           { return v.x * v.x + v.y * v.y; }
inline float vlen  (vec2 v)           { return (float)sqrt(vlen2(v)); }
inline float vdot  (vec2 v1, vec2 v2) { return v1.x * v2.x + v1.y * v2.y; }
inline vec2  vunit (float angle)      { return vmake((float)cos(angle), (float)sin(angle)); }

//-----------------------------------------------------------------------------
void CORE_RenderCenteredSprite(vec2 pos, vec2 size, GLuint texid)
{
  vec2 p0 = vsub(pos, vscale(size, .5f));
  vec2 p1 = vadd(pos, vscale(size, .5f));

  glBindTexture( GL_TEXTURE_2D, texid );
  glBegin( GL_QUADS );
  glTexCoord2d(0.0,0.0); glVertex2f(p0.x, p0.y);
  glTexCoord2d(1.0,0.0); glVertex2f(p1.x, p0.y);
  glTexCoord2d(1.0,1.0); glVertex2f(p1.x, p1.y);
  glTexCoord2d(0.0,1.0); glVertex2f(p0.x, p1.y);
  glEnd();
}

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
};
#define NUM_BALLS 50//12
Ball balls[NUM_BALLS];

#define MAX_BALL_SPEED 2.f
#define JUMP_SPEED 100.0f//20.f
#define THRESHOLD_BRAKE_X 1.f
#define THRESHOLD_STOP_Y 1.f
#define THRESHOLD_STOP  (SYM_EPSILON*1000)
#define MIN_REACTIVATION_ENERGY 500.0f


bool collided[NUM_BALLS][NUM_BALLS+1];
bool deactivated[NUM_BALLS];

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

  //if( deactivated[i])
  //{
	 // float imp = -( 1.0f + rest)*vdot(v2, e);
	 // balls[j].vel=vadd(balls[j].vel, vscale(e, imp ));
  //}
  //else
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
	  }
	  else
	  {
		  assert( v21n > (-SYM_EPSILON));
	  }


	}
}
void solve_wallColisions()
{
		float wall_rest=1.0f;//0.8f;
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
      if (balls[i].vel.y < 0.f &&(balls[i].pos.y - balls[i].radius) < 0)
      {
        // Rebound
        balls[i].vel.y *= -wall_rest;//-0.8f;
        balls[i].pos.y = balls[i].radius; // This causes re-interpenetration, and sometimes great instability!

        // Stop nearly stopped balls at the ground
		if (vlen2(balls[i].vel) < THRESHOLD_STOP)
//        if (fabs(balls[i].vel.y) < THRESHOLD_STOP_Y)
        {
          balls[i].vel.y = 0.f;
          balls[i].vel.x = 0.f;
          // THINGS THAT DONT WORK WELL:
          //balls[i].vel.y = -0.01f * (balls[i].pos.y - balls[i].radius); // Fix it a bit upwards, works better, but it's unstable
		  deactivated[i]=true;
        }
      }
	}

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
    balls[i].vel = vadd(balls[i].vel, vscale(GRAVITY,delta_time));
    balls[i].vel = vscale(balls[i].vel, (1.f - AIR_FRICTION));
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
	//integrate velocity
    balls[i].pos = vadd(balls[i].oldpos, vscale(balls[i].vel,delta_time));
}
bool checkCollide(int i)
{
	  collided[i][NUM_BALLS] = false;

      for (int j = 0; j < NUM_BALLS; j++)
	  {
		if (i != j)
        {
          float limit2 = (balls[i].radius + balls[j].radius) * (balls[i].radius + balls[j].radius);
		  limit2+=SYM_EPSILON;
		  //if  ojects are interpenetrated, let them pass through
          if ( vlen2(vsub(balls[i].oldpos, balls[j].pos)) > limit2 &&
				vlen2(vsub(balls[i].pos, balls[j].pos)) <= limit2)
          {
            collided[i][NUM_BALLS] = true;
			collided[i][j] = true;
			collided[j][i] = true;
//            break;
          }
		  else
		  {
			collided[i][j] = false;
			collided[j][i] = false;
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
	if( collided[i][j])
	{
		if( deactivated[j])
		{
			float energy=.5f*balls[i].mass*vlen2(balls[i].vel);

			if( energy > MIN_REACTIVATION_ENERGY)
			{
				deactivated[j]=false;
			}
			solve_collision(i, j,restitution);
			//cascade deactivation
			if (vlen2(balls[i].vel) < THRESHOLD_STOP)
			{
				deactivated[i]=true;
			}
		}
		else
		{
		// Rebound against the other ball! (but only once)
//					if (!collided[j][i])
			solve_collision(i, j,restitution);
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
    if (CORE_FRand(0.f, 1.f) < 0.1f)
    {
      radius = 48.f;
      balls[i].radius = radius;
      balls[i].mass = 10.f;
      balls[i].gfx = texlargeball;
    }
    else
    {
      radius = 16.f;
      balls[i].radius = radius;
      balls[i].mass = 1.f;
      balls[i].gfx = texsmallball;
    }
    balls[i].pos = vmake(CORE_FRand(radius, SCR_WIDTH-radius), CORE_FRand(radius, SCR_HEIGHT-radius));
    balls[i].vel = vmake(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
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
  memset(collided, 0, sizeof(collided));
  while (!SYS_GottaQuit())
  {
    // Render
    glClear( GL_COLOR_BUFFER_BIT );

    // Render backgground
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 4; j++)
        CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f), vmake(128.f, 128.f), texbkg);

    // Render balls
    for (int i = 0; i < NUM_BALLS; i++)
      //if (i == 6)
      CORE_RenderCenteredSprite(balls[i].pos, vmake(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);

    SYS_Show();
#ifdef _DEBUG
	float energy=getEnergy();
#endif
    // Run balls and intercollisons
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

	assert(new_energy < (energy*2.0));
#endif

    // Keypress!
    if (SYS_KeyPressed(' '))
    {
	  memset(deactivated, 0, sizeof(deactivated));

      for (int i = 0; i < NUM_BALLS; i++)
        if (balls[i].pos.y - balls[i].radius < 5.f)
        {
          if (fabs(balls[i].vel.x) < 1.f)
            balls[i].vel.x = CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED);
          balls[i].vel.y = CORE_FRand(0, JUMP_SPEED);
        }
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