#include<windows.h>
#include"resource.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
enum tag_Major {MANAGE, KOREAN, ENGLISH, LAW} Major;
TCHAR* arMajor[] = { TEXT("�濵�а�"),TEXT("�����а�"),TEXT("�����а�"),TEXT("���а�") };
LPCTSTR lpszClass = TEXT("Class");

BOOL CALLBACK MajorDlgProc(HWND Major, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_MALE, bMale ? BST_CHECKED : BST_UNCHECKED);
		CheckRadioButton(hDlg, IDC_MAJOR1, IDC_MAJOR4, IDC_MAJOR + Major);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			bMale = (lsDlgButtonChecked(hDlg, IDC_MALE) == BST_CHECKED);
			if (IsDlgButtonChecked(hDlg, IDC_MAJOR1) == BST_CHECKED) Major = MANAGE;
			if (IsDlgButtonChecked(hDlg, IDC_MAJOR2) == BST_CHECKED) Major = KOREAN;
			if (IsDlgButtonChecked(hDlg, IDC_MAJOR3) == BST_CHECKED) Major = ENGLISH;
			if (IsDlgButtonChecked(hDlg, IDC_MAJOR4) == BST_CHECKED) Major = LAW;
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
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
	TCHAR str[128];
	
	switch (iMessage) {
	case WM_CREATE:
		bMale = TRUE;
		Major = KOREAN;
		return 0;
	case WM_LBUTTONDOWN:
		if (DialogBox(g_hIst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MajorDlgProc) == IDOK) {
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		wsprintf(str, TEXT("���� = %s"), bMale ? TEXT("����") : TEXT("����"));
		TextOut(hdc, 10, 10, str, lstrlen(str));
		wsprintf(str, TEXT("���� = %s"), arMajor[Major]);
		TextOut(hdc, 10, 30, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}