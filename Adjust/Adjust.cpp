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

void SetClientRect(HWND hWnd, int width, int height) {
	RECT crt;
	DWORD Style, ExStyle;

	SetRect(&crt, 0, 0, width, height);
	Style = GetWindowLong(hWnd, GWL_STYLE);
	ExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	AdjustWindowRectEx(&crt, Style, GetMenu(hWnd) != NULL, ExStyle);
	if (Style & WS_VSCROLL) crt.right += GetSystemMetrics(SM_CYVSCROLL);
	if (Style & WS_HSCROLL) crt.bottom += GetSystemMetrics(SM_CXVSCROLL);
	SetWindowPos(hWnd,NULL,0,0,crt.right-crt.left,crt.bottom-crt.top,SWP_NOMOVE|SWP_NOZORDER);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT crt;

	switch (iMessage) {
	case WM_CREATE:
		SetClientRect(hWnd, 300, 200);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 0, 0, 300, 200);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

