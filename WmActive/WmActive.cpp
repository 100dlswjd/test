#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PopupProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("PopupClass");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = PopupProc;
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
	static TCHAR Mes[128];
	static HWND hPopup;

	switch (iMessage) {
	case WM_CREATE:
		hPopup = CreateWindow(TEXT("PopupClass"), TEXT("팝업 윈도우"), WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE, 410, 100, 300, 300, hWnd, (HMENU)0, g_hInst, NULL);
		return 0;
	case WM_ACTIVATEAPP:
		if (wParam == TRUE) {
			ShowWindow(hPopup, SW_SHOWNOACTIVATE);
		}
		else {
			ShowWindow(hPopup, SW_HIDE);
		}
		return 0;
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE) {
			lstrcpy(Mes, TEXT("비활성화 상태입니다."));
		}
		else {
			lstrcpy(Mes, TEXT("저는 지금 활성화 되어있습니다."));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK PopupProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR Mes[128];

	switch (iMessage) {
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE) {
			lstrcpy(Mes, TEXT("비활성화 상태입니다."));
		}
		else {
			lstrcpy(Mes, TEXT("저는 지금 활성화 되어 있습니다."));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}