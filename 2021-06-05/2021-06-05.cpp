#include<stdio.h>
void show0(void);
void show1(void);
void show2(void);

int main() {
	void (*pM[3])(void);
	int num;

	pM[0] = show0;
	pM[1] = show1;
	pM[2] = show2;

	printf("실행할 번호입력 0,1,2 :  ");
	scanf_s("%d", &num);
	
	if (num < 3) {
		pM[num]();
	}
}

void show0() {
	printf("0번 눌렀다");
}

void show1() {
	printf("1번 눌렀다");
}

void show2() {;
	printf("2번 눌렀다");
}