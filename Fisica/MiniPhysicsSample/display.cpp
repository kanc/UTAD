
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

#include "display.h"


//-----------------------------------------------------------------------------
int Main(void);

//-----------------------------------------------------------------------------

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
bool SYS_KeyPressed(int key)
{
  return (GetAsyncKeyState(key) & 0x8000) != 0;
}
void SYS_Sleep(int ms)
{
  Sleep(ms);
}

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
	  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
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
