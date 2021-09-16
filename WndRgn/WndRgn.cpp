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
	PAINTSTRUCT ps;
	UINT nHit;
	HRGN hWndRgn;

	switch (iMessage) {
	case WM_CREATE:
		hWndRgn = CreateEllipticRgn(0, 0, 200, 200);
		SetWindowRgn(hWnd, hWndRgn, FALSE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 0, 0, 199, 199);
		Rectangle(hdc, 40, 50, 160, 150);
		TextOut(hdc, 45, 90, TEXT("스페이스-종료"),16);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_SPACE) {
			DestroyWindow(hWnd);
		}
		return TRUE;
	case WM_NCHITTEST:
		nHit = DefWindowProc(hWnd, iMessage, wParam, lParam);
		if (nHit == HTCLIENT) {
			nHit = HTCAPTION;
		}
		return nHit;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


