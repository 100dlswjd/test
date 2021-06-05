#include<stdio.h>
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);

int main() {
	int (*pM[3])(int a, int b);
	int a, b;
	printf("a값 b값 입력 :");
	scanf_s("%d %d", &a, &b);

	pM[0] = add;
	pM[1] = sub;
	pM[2] = mul;

	int num;
	printf("\n번호입력\n1번 : add\n2번 : sub\n3번 : mul\n");
	scanf_s("%d", &num);

	int res = (*pM[num-1])(a,b);
	
	printf("\n\n 결과값 : %d", res);
}

int add(int a, int b) {
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}

int mul(int a, int b) {
	return a * b;
}