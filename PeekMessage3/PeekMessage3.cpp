#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

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
	int i;
	TCHAR str[256];
	MSG Message;

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		for (i = 0; i < 2000000; i++) {
			if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
				if (Message.message == WM_QUIT) {
					PostQuitMessage(0);
					return 0;
				}
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
			SetPixel(hdc, rand() % 500, rand() % 400, RGB(rand() % 256, rand() % 256, rand() % 256));
		}
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_CHAR:
		wsprintf(str, TEXT("%c 문자 입력"), wParam);
		SetWindowText(hWnd, str);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

