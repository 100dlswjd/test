#include<stdio.h>
#include<stdlib.h>

int main() {
	int num;
	int i = 0;
	printf("х╫╪Ж ют╥б : ");
	scanf_s("%d", &num);
	char* a;
	a = (char*)malloc(sizeof(char) * (num + 1));
	for (i; i < num; i++) {
		a[i] = 97 + i;
	}
	a[num] = '\0';
	
	printf("%s", a);
	free(a);
}