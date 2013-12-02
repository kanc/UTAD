#define WIN32_LEAN_AND_MEAN 

#include <windows.h> 
#include <windowsx.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const char g_className[] = "Practica 1";
COLORREF g_actualColor;

// dimensiones de la ventana
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{ 
	switch(msg)
	{	
		case WM_DESTROY: 
			PostQuitMessage(0);
			return 0;			

       case WM_PAINT:
        {
			char text[100];
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint (hwnd, &ps);

			// -----> aquí va el pintado

			POINT point;
			GetCursorPos( &point );
			ScreenToClient(hwnd, &point );

			SetPixel(hdc,point.x,point.y,g_actualColor);
			
            EndPaint (hwnd, &ps);			
        }
		break;
	   
	   case WM_KEYDOWN:		
			if (wparam == 0x53) //tecla S
				Beep(1230,123);
					
			break;

		case WM_MOUSEMOVE:		
			InvalidateRect(hwnd,NULL,false);					
			break;

		case WM_LBUTTONDOWN:
			g_actualColor = RGB(0,255,0);
			break;

		case WM_LBUTTONUP:
			g_actualColor = RGB(255,255,255);
			break;

		case WM_RBUTTONDOWN:
			g_actualColor = RGB(255,0,0);
			break;

		case WM_RBUTTONUP:
			g_actualColor = RGB(255,255,255);
			break;


		default:
			return (DefWindowProc(hwnd, msg, wparam, lparam));
	} 

	return 0;
} 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{	
	WNDCLASSEX sd;
	MSG msg;
	HWND hwnd;

	sd.cbSize= sizeof(WNDCLASSEX);
	sd.style			= CS_HREDRAW | CS_VREDRAW;
	sd.lpfnWndProc		= WndProc;
	sd.cbClsExtra		= 0;
	sd.cbWndExtra		= 0;
	sd.hInstance		= hinstance;
	sd.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	sd.hCursor			= LoadCursor(NULL, IDC_ARROW);
	sd.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	sd.lpszMenuName		= NULL;
	sd.lpszClassName	= g_className;
	sd.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&sd))
	{
		MessageBox(NULL, "Error al registar la clase!", "Error!",MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	if (!(hwnd = CreateWindowEx(NULL, g_className, "Practica 1", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hinstance, NULL)))	
		return(0);

	// Oculta el cursor del ratón
	ShowCursor( false );

	g_actualColor=RGB(255,255,255);

	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} 

	return(msg.wParam);
} 
