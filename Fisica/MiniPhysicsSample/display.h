#ifndef	DISPLAY_HEADER_H
#define DISPLAY_HEADER_H

#include "vector.h"

#define SCR_WIDTH  600//800
#define SCR_HEIGHT 400//600
#define SCR_FULLSCREEN 0
#define READ_LE_DWORD(a) (a[0] + a[1]*0x100 + a[2]*0x10000 + a[3]*0x1000000)

//-----------------------------------------------------------------------------
#define SYS_KEY_UP    VK_UP
#define SYS_KEY_DOWN  VK_DOWN
#define SYS_KEY_LEFT  VK_LEFT
#define SYS_KEY_RIGHT VK_RIGHT
////////////////////////////////////////////////
typedef unsigned       char byte;
typedef unsigned short int  word;
typedef unsigned       int  dword;

//-----------------------------------------------------------------------------
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

bool SYS_GottaQuit();
void SYS_Show();
void SYS_Pump();
bool SYS_KeyPressed(int key);
void SYS_Sleep(int ms);
GLuint CORE_LoadBmp(const char filename[], bool wrap);
void CORE_UnloadBmp(GLuint texid);
void CORE_RenderCenteredSprite(vec2 pos, vec2 size, GLuint texid);

inline float CORE_FRand(float from, float to)
{
  return from + (to-from)*(rand()/(float)RAND_MAX);
}

#endif