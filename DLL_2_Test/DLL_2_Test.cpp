// DLL_2_Test.cpp : DLL을 위해 내보낸 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DLL_2_Test.h"


// 내보낸 변수의 예제입니다.
DLL2TEST_API int nDLL2Test=0;

// 내보낸 함수의 예제입니다.
DLL2TEST_API int fnDLL2Test(void)
{
    return 0;
}

// 내보낸 클래스의 생성자입니다.
CDLL2Test::CDLL2Test()
{
    return;
}
