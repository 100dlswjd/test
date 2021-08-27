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
	CONST TCHAR* NotePad = TEXT("NotePad");
	HWND hNotePad;
	CONST TCHAR* Mes = TEXT("1: 메모장 즉시 활성화 , 2,4:메모장 3초 후에 활성화,");//TEXT("3,5:3초후 스스로 활성화");
	hNotePad = FindWindow(NotePad, NULL);
	switch (iMessage) {
	case WM_CREATE:
		
		if (hNotePad == NULL) {
			MessageBox(NULL, TEXT("이 예제를 실행하기 전에 메모장을 실행하십시오."), TEXT("알림"), MB_OK);
			return -1;
		}
		return -1;
	case WM_KEYDOWN:
		switch (iMessage) {
		case '1':
			//SetActiveWindow(hNotePad);
			SetForegroundWindow(hNotePad);
			break;
		case '2':
			SetTimer(hWnd, 2, 3000, NULL);
			break;
		case '3':
			SetTimer(hWnd, 3, 3000, NULL);
			break;
		case '4':
			SetTimer(hWnd, 4, 3000, NULL);
			break;
		case '5':
			SetTimer(hWnd, 4, 3000, NULL);
			break;
		}
		return 0;
	case WM_TIMER:
		switch (wParam) {
		case 2:
			KillTimer(hWnd, 2);
			SetForegroundWindow(hNotePad);
			break;
		case 3:
			KillTimer(hWnd, 3);
			SetForegroundWindow(hWnd);
			break;
		case 4:
			KillTimer(hWnd, 4);
			SetForegroundWindow(hNotePad);
			break;
		case 5:
			KillTimer(hWnd, 4);
			SetForegroundWindow(hWnd);
			break;
		}
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

