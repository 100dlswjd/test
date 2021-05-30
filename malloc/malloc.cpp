#include<stdio.h>
#include<stdlib.h>

int main() {
	char* a;
	int num;
	char arr[100];
	printf("입력 :");
	scanf_s("%d", &num);
	a =(char*) malloc(sizeof(char) * (num+1));
	for (int i=0;i<num;i++) {
		a[i] = 'a';
	}
	a[num] = '\0';
	printf("%s\n", a);
	printf("malloc 후 %d\n", sizeof(char*));


	printf("그냥 선언 %d", sizeof(arr));
	free(a);
	return 0;
}