#include<windows.h>

#define ID_LISTBOX 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hList;
LPCTSTR lpszClass = TEXT("Class");

BOOL CALLBACK MyEnumWindowsProc(HWND hwnd, LPARAM lParam) {
	TCHAR str[300];
	TCHAR Cap[255];
	RECT rt;

	GetWindowText(hwnd, Cap, 255);
	GetWindowRect(hwnd, &rt);

	wsprintf(str, TEXT("핸들=0x%x(%d), 캡션 = %s, 좌표=(%d,%d,%d,%d)"), hwnd, hwnd, Cap, rt.left, rt.top, rt.right, rt.bottom);
	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);

	return TRUE;
}


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
	CONST TCHAR* Mes = TEXT("윈도우 바닥을 왼쪽 마우스 버튼으로 클릭하면 윈도우 목록을 보여 드릴게요");

	switch (iMessage) {
	case WM_CREATE:
		// 윈도우 목록을 보여주기 위해 리스트 박스를 하나 생성했다.
		hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_VSCROLL, 10, 10, 100, 200, hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		return 0;
	case WM_LBUTTONDOWN:
		// 리스트 박스를 비우고 윈도우 목록을 조사한다.
		SendMessage(hList, LB_RESETCONTENT, 0, 0);
		EnumWindows(MyEnumWindowsProc, NULL);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_SIZE:
		// 리스트 박스가 항상 윈도우를 가득 채우도록
		MoveWindow(hList, 0, 50, LOWORD(lParam), HIWORD(lParam) - 50, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

