#include<stdio.h>
void swap(int *a, int *b);
int main() {
	int a, b;
	scanf_s("%d %d", &a, &b);
	printf("스왑전 %d %d 값\n",a,b);
	swap(&a, &b);
	printf("스왑후 %d %d 값\n", a, b);
}

void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}