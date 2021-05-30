#include<stdio.h>

int main() {
	FILE* fp;
	int a = fopen_s(&fp, "test.txt", "r");
	if (a == 0) {
		printf("성공");
	}
	else {
		printf("실패");
	}
	fclose(fp);
}