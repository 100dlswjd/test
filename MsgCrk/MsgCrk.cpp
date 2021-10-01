// MsgCrk.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "MsgCrk.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MSGCRK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MSGCRK));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MSGCRK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MSGCRK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rt;
    CONST TCHAR* Mes = TEXT("메시지 크랙커를 사용하는 예제입니다.");
    TCHAR str[MAX_PATH];
    static int Count;

          
    switch (iMessage) 
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 1000, NULL);
        return 0;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);
        SetRect(&rt, 10, 100, 500, 120);
        FillRect(hdc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
        lstrcpy(str, TEXT("마우스 왼쪽 버튼을 눌렀습니다."));
        TextOut(hdc, 10, 100, str, lstrlen(str));
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_KEYDOWN:
        hdc = GetDC(hWnd);
        SetRect(&rt, 10, 80, 500, 100);
        FillRect(hdc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
        wsprintf(str, TEXT("%c 키를 눌렀습니다."), wParam);
        TextOut(hdc, 10, 80, str, lstrlen(str));
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_TIMER:
        hdc = GetDC(hWnd);
        SetRect(&rt, 10, 40, 500, 80);
        FillRect(hdc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
        wsprintf(str, TEXT("%d 초 경과했습니다."), Count++);
        TextOut(hdc, 10, 60, str, lstrlen(str));
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_SIZE:
        hdc = GetDC(hWnd);
        SetRect(&rt, 10, 40, 500, 60);
        FillRect(hdc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
        wsprintf(str, TEXT("현재 장업영역의 크기 : %d * %d"), LOWORD(lParam), HIWORD(lParam));
        TextOut(hdc, 10, 40, str, lstrlen(str));
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        KillTimer(hWnd, 0);
        PostQuitMessage(0);
        return 0;        
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
