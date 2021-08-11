#include<windows.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");
BOOL bMale;
enum tag_Major { MANAGE, KOREAN, ENGLISH, LAW }Major;
const TCHAR* arMajor[] = { TEXT("경영학과"),TEXT("국문학과"),TEXT("영문학과"),TEXT("법학과") };

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



BOOL CALLBACK MajorDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_MALE, bMale ? BST_CHECKED : BST_UNCHECKED);
		CheckRadioButton(hDlg, IDC_MAJOR1, IDC_MAJOR4, IDC_MAJOR1 + Major);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			bMale = (lsDlgButtonChecked(hDlg, IDC_MALE) == BST_CHEDCKED);
			if (lsDlgButtonChecked(hDlg, IDC_MAJOR1) == BST_CHECKED)Major = MANAGE;
			if (lsDlgButtonChecked(hDlg, IDC_MAJOR2) == BST_CHECKED)Major = KOREAN;
			if (lsDlgButtonChecked(hDlg, IDC_MAJOR3) == BST_CHECKED)Major = ENGLISH;
			if (lsDlgButtonChecked(hDlg, IDC_MAJOR4) == BST_CHECKED)Major = LAW;
			EndDialog(hDlg, IDOK);
			return TRUE;
		}
		break;
	}
	return FALSE;
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
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MajorDlgProc) == IDOK) { InvalidateRect(hWnd, NULL, TRUE); }
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		wsprintf(str, TEXT("성별 = %s"), bMale ? TEXT("남자") : TEXT("여자"));
		TextOut(hdc, 10, 10, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
 