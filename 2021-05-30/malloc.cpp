#include<stdio.h>
#include<stdlib.h>

int main() {
	int num;
	int i = 0;
	printf("���� �Է� :");
	scanf_s("%d", &num);// 3
	char* a; // a �� ??~ NULL o423984732894s 0
	a = (char*)malloc(sizeof(char) * (num + 1)); // �����ϳ��� 1����Ʈ ����>?  // 4 xx 0 1 2 3 [?]
	for(i; i < num ; i++) { // 0 1 2 3
		a[i] = 97 + i; // 97 = ���ڷ� ��Ÿ���� a ���� ?  // 3
	}
	a[num] = '\0'; // a[4] c ���� a[4] = "aaaa'\0'"
	printf("%s \n", a); // \n �ٹٲ� <br>
	free(a);
	printf("�޸� ������\n");
	printf("%s", a);
}