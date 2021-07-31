// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL,TEXT("하이 ?"), TEXT("경고"), MB_OK);
        OutputDebugString(TEXT("야야 됐냐 ?"));
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        MessageBox(NULL, TEXT("반나서 반가웠따."), TEXT("!!!!가지마!!!!"), MB_OK);
        OutputDebugString(TEXT("나간다."));
        break;
    }
    return TRUE;
}

