#include<stdio.h>
#include<stdlib.h>

int main() {
	int num;
	int i = 0;
	printf("길이 입력 :");
	scanf_s("%d", &num);// 3
	char* a; // a 값 ??~ NULL o423984732894s 0
	a = (char*)malloc(sizeof(char) * (num + 1)); // 문자하나는 1바이트 ㅇㅋ>?  // 4 xx 0 1 2 3 [?]
	for(i; i < num ; i++) { // 0 1 2 3
		a[i] = 97 + i; // 97 = 문자로 나타내면 a ㅇㅋ ?  // 3
	}
	a[num] = '\0'; // a[4] c 언어는 a[4] = "aaaa'\0'"
	printf("%s \n", a); // \n 줄바꿈 <br>
	free(a);
	printf("메모리 해제후\n");
	printf("%s", a);
}