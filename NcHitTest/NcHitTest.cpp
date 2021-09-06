#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("NcHitTest");

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
	RECT crt;
	int i;
	int nHit;
	POINT mpt;
	CONST TCHAR* Mes = TEXT("WM_NCHITTEST 메시지를 활용하는 예제입니다.");

	switch (iMessage) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &crt);
		for (i = 50; i > 0; i -= 5) {
			MoveToEx(hdc, crt.right, crt.bottom - i, NULL);
			LineTo(hdc, crt.right - i, crt.bottom);
		}
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_NCHITTEST:
		GetClientRect(hWnd, &crt);
		mpt.x = LOWORD(lParam);
		mpt.y = HIWORD(lParam);
		ScreenToClient(hWnd, &mpt);
		if (mpt.y > -mpt.x - 50 + crt.right + crt.bottom) {
			nHit = HTBOTTOMRIGHT;
		}
		else {
			nHit = DefWindowProc(hWnd, iMessage, wParam, lParam);
			switch (nHit) {
			case HTCLIENT:
				nHit = HTCAPTION;
				break;
			case HTLEFT:
				nHit = HTMAXBUTTON;
				break;
			case HTMINBUTTON:
				nHit = HTCLOSE;
				break;
			case HTMAXBUTTON:
				nHit = HTMINBUTTON;
				break;
			case HTCLOSE:
				nHit = HTLEFT;
				break;
			}
		}
		return nHit;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;		
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
