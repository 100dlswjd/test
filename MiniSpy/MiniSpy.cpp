#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("MiniSpy");

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
	POINT pt;
	HWND hWndPoint, hWndParent;
	static HWND hWndOld;
	static TCHAR str[256];
	TCHAR sCaption[256], sClass[256];
	RECT crt;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 500, NULL);
		return 0;
	case WM_TIMER:
		GetCursorPos(&pt);
		hWndPoint = WindowFromPoint(pt);
		if (hWndPoint == hWndOld) {
			return 0;
		}
		hWndOld = hWndPoint;
		if (hWndPoint == NULL) {
			lstrcpy(str, TEXT("윈도우 없음"));
		}
		else {
			GetWindowText(hWndPoint, sCaption, 256);
			GetClassName(hWndPoint, sClass, 256);
			hWndParent = GetParent(hWndPoint);
			GetWindowRect(hWndPoint, &crt);
			wsprintf(str, TEXT("핸들 : %d(0x%x)\r\n 클래스 : %s\r\n 캡션 : %s\r\n")TEXT("Parent : %d(0x%x)\r\n")TEXT("Rect : (%d,%d) - (%d,%d), %d*%d"),
				hWndPoint, hWndPoint, sClass, sCaption, hWndParent, hWndParent, crt.left, crt.top, crt.right, crt.bottom, crt.right - crt.left, crt.bottom - crt.top);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &crt);
		DrawText(hdc, str, -1, &crt, 0);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

