// https://code.google.com/p/g4c-lib/
// Tweaked by Javier Arevalo

#pragma once

#include <windows.h>
#include <vector>
using namespace std;

#include "g4c_simple.h"

const int winWidth=640;
const int winHeight=480;
const int textBuffersize=300;

class Sprite
{
public:
	
	int index;

	HBITMAP bmp;
	HBITMAP bmpMask;
	HPALETTE pal;
	int x,y,w,h;

	int visible;
	int collidable;
	Sprite();
	void SwapBitmapWith(Sprite *);
	void LoadBmp(LPCWSTR fname);
	void CleanUp();
	int isHit(Sprite &spr2);
	void Draw(HDC dc);
	void DrawNoTransparency(HDC dc);
	void DrawNoTransparency(HDC dc,int newX,int newY);
	RECT GetRect();
};
//const int maxSprites=30;
class Buffer
{
public:
	int w,h;
	HDC memDC;
	HBITMAP bmp,oldbmp;
	void Init(int _w,int _h,HDC dc);
	void Destroy();
	void Blit(HDC dc,int x,int y);
};
class Timer
{
public:
	const static int minDelay=33;
	long timeTillNextFrame;
	long lastTime;
	int elapsedFrames;
	double avgFrameRate;
	long sumDelays;
	void Update(long curTime);
	Timer();
	
};
class GWnd
{
public:
	HWND hWnd;
	bool canDraw;
	HBITMAP bmp;
	HBITMAP hOldBmp;
	HDC memDC;


	int width,height;
	HANDLE evCanDraw;
	HANDLE mxUseDC;

	HPEN hOldPen;
	HBRUSH hOldBrush;

	int default_pen;
	int default_brush;

	static HPEN pentable[16];
	static HBRUSH brushtable[16];
	static COLORREF colortable[16];

	vector<Sprite> sprites;
	Buffer spriteLayer;
	static SpriteProc sprProc;
	static MouseProc mouseProc;
	static KeyProc keyDownProc;
	static KeyProc keyUpProc;
	bool keyPressed;
	int pressedChar;
	bool textInputState;
	char inputBuffer[textBuffersize];
	int inputBufferIndex;

	bool rightMouseDown,leftMouseDown;
	HANDLE hEvInputState;
	void EnterInputState();
	void WaitForEndInput();
	void DrawCurrentTextInput();
	void OnChar(int ch);
	void OnSetFocus();
	void OnKillFocus();
	int nCaretPosX,nCaretPosY;
	int textInputStartX,textInputStartY;
	int dwCharY ;
	bool caretVisible;
	
	void ShowCaret();
	void HideCaret();
	int GetStrWidth(char *);

	Timer timer;
	bool appRunning;
	GWnd();
	void OnPaint(HDC dc, PAINTSTRUCT * ps);
	void UpdateCollission();
	int IsCollission(int i,int j);
	void Resize(int cx,int cy);
	void PreparememDC(HDC);
	void OnCreate(void);
	void CleanUp();
	void WaitTillCanDraw();
	void Invalidate();
	void DrawSprites();
	void SetText(LPCTSTR t);
	void OnIdle();
	void OnKeyDown(int virtualCode);
	void OnKeyUp(int virtualCode);
	void OnMouseMove(int x,int y);
	void StopDrawing();
	static void InitPenTable();
	static void InitBrushTable();
	static void InitColorTable();
	void SelectPen(int clr);
	void RestorePen();
	void SelectBrush(int clr);
	void RestoreBrush();
	void SelectTextColor(int clr);


};

BOOL LoadBitmapFromBMPFile(LPCWSTR szFileName, HBITMAP *phBitmap,
   HPALETTE *phPalette,int &w,int &h );
void DrawBmp(HDC hDC,HBITMAP hBitmap,HPALETTE hPalette,int x,int y,DWORD rop=SRCCOPY);
HBITMAP CreateBitmapMask(HDC dc,HBITMAP hbmColour, COLORREF crTransparent);
extern GWnd *gWnd;
