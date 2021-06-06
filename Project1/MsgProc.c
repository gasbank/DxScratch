#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

extern int gQuit;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			gQuit = 1;
			PostQuitMessage(0);
		}
		break;
	case WM_DESTROY:
		gQuit = 1;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
