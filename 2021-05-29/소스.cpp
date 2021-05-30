// ¾Ï»ì
#include<stdio.h>

int amsal() {
	FILE *fp;
	fopen_s(&fp,"test.txt", "w");
	
	fclose(fp);

	return 0;
}