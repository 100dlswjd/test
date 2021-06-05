#include<stdio.h>
int add(int a, int b);
int main() {
	int add(int x, int y);
	int (*pM)(int x, int y);
	pM = add;

	int res = (*pM)(5, 10);

	printf("%d", res);
}

int add(int a, int b) {
	int answer = a + b;
	return answer;
}