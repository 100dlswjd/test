#include<stdio.h>
#include<stdlib.h>

int main() {
	char* a;
	int num;
	char arr[100];
	printf("�Է� :");
	scanf_s("%d", &num);
	a =(char*) malloc(sizeof(char) * (num+1));
	for (int i=0;i<num;i++) {
		a[i] = 'a';
	}
	a[num] = '\0';
	printf("%s\n", a);
	printf("malloc �� %d\n", sizeof(char*));


	printf("�׳� ���� %d", sizeof(arr));
	free(a);
	return 0;
}