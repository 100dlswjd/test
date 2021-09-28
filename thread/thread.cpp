#include<stdio.h>
#include<windows.h>

DWORD WINAPI ThreadFunc(LPVOID);

int count = 0;


int main() {

	/*for (;;) {
		printf("dddddd call\n");
	}*/

	HANDLE hThrd;
	DWORD threadId;
	
	hThrd = CreateThread(NULL, 0, ThreadFunc, (LPVOID)NULL, 0, &threadId);

	if (hThrd) {
		printf("Thread ddddddd  \n");
		CloseHandle(hThrd);
	}
	

	for (;;) {
		// count += 1;
		printf("dddddd call %d \n", count);
		Sleep(1000);
	}
	
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID) {
	int i=0;
	for ( ; ; i++) {
		printf("Call back %d \n", count);
		count += 1;
		Sleep(5000);
	}
	return 0;
}