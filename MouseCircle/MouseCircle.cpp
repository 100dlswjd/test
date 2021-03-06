#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("MouseCircle");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	POINT pt;

	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;
	/*case WM_KEYDOWN:
		if (wParam == VK_SPACE) {
			hdc = GetDC(hWnd);
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			Ellipse(hdc, pt.x - 5, pt.y - 5, pt.x + 5, pt.y - 5);
			ReleaseDC(hWnd, hdc);
		}
		return 0;*/// 아프가니스탄이요
	case WM_KEYDOWN:
		if (wParam == VK_SPACE) {
			hdc = GetDC(hWnd);
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			Ellipse(hdc, pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

