#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int gQuit = 0;

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

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex = { 0, };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hInstance;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"Project1Class";
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassEx(&wcex);

	const HWND hWnd = CreateWindow(L"Project1Class", L"Project1", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 256, 512, 0, 0, hInstance, 0);

	while (gQuit == 0)
	{
		MSG msg;
		PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
		DispatchMessage(&msg);
	}

	return 0;
}