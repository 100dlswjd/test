#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpezCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("WM_LBUTTONDOWN"), 15);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("WM_RBUTTONDOWN"), 15);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_RBUTTONUP:
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("WM_RBUTTONUP"), 12);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_LBUTTONUP:
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("WM_LBUTTONUP"), 12);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd ,&ps);
		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
