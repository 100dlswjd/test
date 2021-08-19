#include<windows.h>

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildLeftProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildTopProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildBottomProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
// ������ �ڵ�
HWND hWndMain, hC1, hC2, hC3;
LPCTSTR lpszClass = TEXT("Childs");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	static HBRUSH hRedBrush, hBlueBrush, hGreenBrush;

	hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	hBlueBrush = CreateSolidBrush(RGB(0, 255, 0));
	hGreenBrush = CreateSolidBrush(RGB(0, 0, 255));

	// ���� ������ Ŭ����
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = NULL;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	// ���� ���ϵ� Ŭ����
	WndClass.hbrBackground = hRedBrush;
	WndClass.lpfnWndProc = ChildLeftProc;
	WndClass.lpszClassName = TEXT("ChildLeft");
	RegisterClass(&WndClass);

	// ���� ���ϵ�
	WndClass.hbrBackground = hGreenBrush;
	WndClass.lpfnWndProc = ChildTopProc;
	WndClass.lpszClassName = TEXT("ChildTop");
	RegisterClass(&WndClass);

	// �Ʒ��� ���ϵ�
	WndClass.hbrBackground = hBlueBrush;
	WndClass.lpfnWndProc = ChildBottomProc;
	WndClass.lpszClassName = TEXT("ChildBottom");
	RegisterClass(&WndClass);

	// ���� ������ ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	hWndMain = hWnd;

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	DeleteObject(hRedBrush);
	DeleteObject(hBlueBrush);
	DeleteObject(hGreenBrush);
	return (int)Message.wParam;
}

// ���� �������� �޽��� ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	RECT crt;

	switch (iMessage) {
	case WM_CREATE:
		hC1 = CreateWindow(TEXT("ChildLeft"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		hC2 = CreateWindow(TEXT("ChildTop"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		hC3 = CreateWindow(TEXT("ChildBottom"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		return 0;
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED) {
			GetClientRect(hWnd, &crt);
			MoveWindow(hC1, 0, 0, 300, crt.bottom, TRUE);
			MoveWindow(hC2, 300, 0, crt.right - 300,150, TRUE);
			MoveWindow(hC3, 300, 150, crt.right - 300, crt.bottom - 150, TRUE);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// ���� ���ϵ� �޽��� ���ν���
LRESULT CALLBACK ChildLeftProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static HWND hList, hEdit, hBtn;
	TCHAR str[256];

	switch (iMessage) {
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("����Ʈ �ڽ�"));
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 210, 10, 80, 25, hWnd, (HMENU)1, g_hInst, NULL);
		hBtn = CreateWindow(TEXT("button"), TEXT("Add"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 50, 80, 25, hWnd, (HMENU)2, g_hInst, NULL);
		return 0;
	case WM_SIZE:
		MoveWindow(hList, 10, 10, 190, HIWORD(lParam) - 20, TRUE);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 2:
			GetWindowText(hEdit, str, 256);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
		}
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// ���� ���ϵ��� �޽��� ���ν���
LRESULT CALLBACK ChildTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	CONST TCHAR* Mes = TEXT("�� ������� ���ϵ带 ������ ���� �ʽ��ϴ�.");

	switch (iMessage) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 50, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// �Ʒ��� ���ϵ��� �޽��� ���ν���
LRESULT CALLBACK ChildBottomProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static HWND hEdit;

	switch (iMessage) {
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		SetWindowText(hEdit, TEXT("����Ʈ ������ �Դϴ�."));
		return 0;
	case WM_SIZE:
		MoveWindow(hEdit, 50, 50, LOWORD(lParam) - 100, HIWORD(lParam) - 100, TRUE);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	
}