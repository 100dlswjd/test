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
	TCHAR Mes[128]=TEXT("���� : ���� �˻�, ������ �񵿱� �˻�,  T : �ð�����");
	static TCHAR str1[128] = TEXT("�˻���"), str2[128]=TEXT("�˻���");
	TCHAR str3[128];
	int i;

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		if (GetKeyState(VK_SHIFT) & 0x8000) {
			lstrcpy(str1, TEXT("���� �˻� : shift Ű�� ������"));
		}
		else {
			lstrcpy(str1, TEXT("���� �˻� : shift Ű�� �� ������"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
			lstrcpy(str2, TEXT("�񵿱� �˻� : shift Ű�� ������"));
		}
		else {
			lstrcpy(str2, TEXT("�񵿱� �˻� : shift Ű�� �� ������"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case 'T':
			for (i = 0; i < 30; i++) {
				wsprintf(str3, TEXT("ī��Ʈ = %d"), i);
				SetWindowText(hWnd, str3);
				Sleep(100);
			}
			break;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		TextOut(hdc, 10, 30, str1, lstrlen(str1));
		TextOut(hdc, 10, 50, str2, lstrlen(str2));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

