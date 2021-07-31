// 다음 ifdef 블록은 DLL에서 내보내는 작업을 더 간소화하는 매크로를 만드는
// 표준 방법입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 DLL2TEST_EXPORTS 기호로
// 컴파일됩니다. 이 DLL을 사용하는 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 포함된 다른 모든 프로젝트에서는
// DLL2TEST_API 함수를 DLL에서 가져오는 것으로 표시되는 반면, 이 DLL에서는
// 이 매크로로 정의된 기호가 내보내지는 것으로 표시됩니다.
#ifdef DLL2TEST_EXPORTS
#define DLL2TEST_API __declspec(dllexport)
#else
#define DLL2TEST_API __declspec(dllimport)
#endif

// 이 클래스는 dll에서 내보낸 것입니다.
class DLL2TEST_API CDLL2Test {
public:
	CDLL2Test(void);
	// TODO: 여기에 메서드를 추가합니다.
};

extern DLL2TEST_API int nDLL2Test;

DLL2TEST_API int fnDLL2Test(void);
