#include<stdio.h>

int main() {
	FILE* fp;
	int a = fopen_s(&fp, "test.txt", "r");
	if (a == 0) {
		printf("����");
	}
	else {
		printf("����");
	}
	fclose(fp);
}