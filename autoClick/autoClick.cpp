#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("autoClick");
int count = 0;

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
	POINT ptMouse;

	switch (iMessage) {
	case WM_HOTKEY:
		if (wParam == 0x0001) {
			SetTimer(hWnd, 0x0001, 10, NULL);
		}
		else {
			KillTimer(hWnd, 0x0001);
		}
		/*GetCursorPos(&ptMouse);
		mouse_event(0x0002, ptMouse.x, ptMouse.y, 0, 0);
		mouse_event(0x0004, ptMouse.x, ptMouse.y, 0, 0);*/
		return 0;
	case WM_TIMER:
		GetCursorPos(&ptMouse);
		mouse_event(0x0002, ptMouse.x, ptMouse.y, 0, 0);
		mouse_event(0x0004, ptMouse.x, ptMouse.y, 0, 0); 
		// 메시지 처리 순서, 타이머 페인트 핫키 
		return 0;
	case WM_CREATE:
		RegisterHotKey(hWnd, 0x0001, 0, VK_LEFT);
		RegisterHotKey(hWnd, 0x0002, 0, VK_RIGHT);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		return 0;	
	case WM_DESTROY:
		UnregisterHotKey(hWnd, 0x0001);
		UnregisterHotKey(hWnd, 0x0002);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

