#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("TripleClick");

DWORD ct[5];
DWORD cp[5];

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

BOOL TextClicks(int n) {
	static DWORD dt = GetDoubleClickTime();
	static int dx = GetSystemMetrics(SM_CXDOUBLECLK);
	static int dy = GetSystemMetrics(SM_CYDOUBLECLK);
	int i;

	if (n < 2 || n > 5) return FALSE;
	for (i = 0; i < n - 1; i++) {
		if (ct[4 - i] - ct[4 - i - 1] > dt) return FALSE;
		if (abs(LOWORD(cp[4 - i]) - LOWORD(cp[4 - i - 1])) > dx) return FALSE;
		if (abs(HIWORD(cp[4 - i]) - HIWORD(cp[4 - i - 1])) > dy) return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	CONST TCHAR* Mes = TEXT("트리플 클릭 검출 테스트 프로그램");
	int i;

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		for (i = 0; i < 4; i++) {
			ct[i] = ct[i + 1];
			cp[i] = cp[i + 1];
		}
		ct[4] = GetMessageTime();
		cp[4] = GetMessagePos();
		if (TextClicks(3)) {
			MessageBox(hWnd, TEXT("트리플 클릭이 검출되었습니다."), TEXT("알림"), MB_OK);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

