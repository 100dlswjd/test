#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

void StartGame();
void RunGame();
void DrawGame(HDC hdc);
void DrawBitmap(HDC hdc, int x,int y,HBITMAP hBit);

struct tag_Mete {
	double x, y;
	double dx, dy;
};
tag_Mete arMete[1000];
int Num;
double sx = 200, sy = 150;
DWORD st;
HBITMAP Ship;
BOOL bStart;
TCHAR sEllapse[32];

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
	RECT rt;

	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		SetRect(&rt, 0, 0, 400, 300);
		AdjustWindowRect(&rt, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
		MoveWindow(hWnd, 100, 100, rt.right - rt.left, rt.bottom - rt.top, FALSE);
		Num = 50;
		srand(GetTickCount());
		Ship = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SHIP));
		bStart = FALSE;
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_RETURN:
			if (!bStart) StartGame();
			break;
		}
		break;
	case WM_TIMER:
		RunGame();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawGame(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DeleteObject(Ship);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void StartGame() {
	int i;
	int t;

	for (i = 0; i < Num; i++) {
		// 초기 위치 결정 . 4변을 1차원화 해서 난수로 배치
		t = rand() % 1400;
		if (t < 400) {
			arMete[i].x = t;
			arMete[i].y = 5;
		}
		else if (t < 700) {
			arMete[i].x = 395;
			arMete[i].y = t - 400;
		}
		else if (t < 1100) {
			arMete[i].x = t - 700;
			arMete[i].y = 295;
		}
		else {
			arMete[i].x = 5;
			arMete[i].y = t - 1100;
		}
		// dx dy 결정
		arMete[i].dx = rand() % 51 / 10.0 - 2.5;
		arMete[i].dy = rand() % 51 / 10.0 - 2.5;
	}

	sx = 200;
	sy = 150;
	bStart = TRUE;
	SetTimer(hWndMain, 1, 20, NULL);
	st = GetTickCount();
}

void RunGame() {
	int i;
	RECT srt;
	POINT pt;

	// 우주선 이동
	if (GetKeyState(VK_LEFT) & 0x8000) {
		if (sx > 2.3) sx -= 2.3;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000) {
		if (sx < 400 - 12 - 2.3) sx += 2.3;
	}
	if (GetKeyState(VK_UP) & 0x8000) {
		if (sy > 2.3) sy -= 2.3;
	}
	if (GetKeyState(VK_DOWN) & 0x8000) {
		if (sy < 300 - 12 - 2.3) sy += 2.3;
	}

	// 우주선의 영역 . 2만큼 여유를 둔다
	SetRect(&srt, (int)sx + 2, (int)sy + 2, (int)sx + 10, (int)sy + 10);

	//운석으,ㅣ 이동
	for (i = 0; i < Num; i++) {
		arMete[i].x += arMete[i].dx;
		arMete[i].y += arMete[i].dy;
		if (arMete[i].x > 400) arMete[i].x = 0;
		if (arMete[i].x < 0) arMete[i].x = 400;
		if (arMete[i].y > 300) arMete[i].y = 0;
		if (arMete[i].y < 0) arMete[i].y = 300;
		pt.x = int(arMete[i].x);
		pt.y = int(arMete[i].y);
		// 우주선과 충돌 판정
		if (PtlnRect(&srt, pt)) {
			KillTimer(hWndMain, 1);
			bStart = FALSE;
		}
	}
	wsprintf(sEllapse,TEXT("%.2f초"),(GetTickCount()-st)/1000.0);
	InvalidateRect(hWndMain, NULL, TRUE);
}

void DrawGame(HDC hdc) {
	int i;

	for (i = 0; i < Num; i++) {
		SetPixel(hdc, int(arMete[i].x), int(arMete[i].y), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x+1), int(arMete[i].y), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x), int(arMete[i].y+1), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x+1), int(arMete[i].y+1), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x-1), int(arMete[i].y), RGB(255, 255, 0));
	}
	DrawBitmap(hdc, (int)sx, (int)sy, Ship);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255, ));
	TextOut(hdc, 350, 5, sEllapse.lstrlen(sEllapse));
}