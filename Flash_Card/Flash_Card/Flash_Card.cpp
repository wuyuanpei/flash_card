// Because the code is too easy, no comment will be written
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <conio.h>

struct word {
	char English[64];
	char Chinese[64];
};

word* list;
int count_lines;

void readfile();
void flash();
int main()
{
	readfile();
	flash();
}

void readfile() {
	FILE* fp;
	char buf[256];
	int count = 0;
	count_lines = 0;
	fopen_s(&fp, "vocab.txt", "r");
	if (fp == NULL) {
		printf("vocab.txt open error!\n");
		exit(-1);
	}
	else {
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			if (strchr(buf, '=') != 0) {
				count_lines++;
			}
		}
	}
	fclose(fp);
	list = (word*)malloc(sizeof(word) * count_lines);
	if (list == NULL) {
		printf("list memory error!\n");
		exit(-2);
	}
	fopen_s(&fp, "vocab.txt", "r");
	if (fp == NULL) {
		printf("vocab.txt open error!\n");
		exit(-1);
	}
	else {
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			char* bound = strchr(buf, '=');
			if (bound != 0) {
				if (*(buf + strlen(buf) - 1) == '\n'){
					*(buf + strlen(buf) - 1) = 0;
				}
				*bound = 0;
				strcpy_s(list[count].English, 64, buf);
				strcpy_s(list[count++].Chinese, 64, bound + 1);
			}
		}
	}
	fclose(fp);
}

void flash() {
	srand((unsigned)time(NULL));
	while(1){
		int idx = rand() % count_lines;
		int len_E = strlen(list[idx].English);
		printf("\n\n\n\n");
		for (int i = 0; i < 26 - ((len_E + 1) >> 1); i++) {
			printf(" ");
		}
		printf("%s\n",list[idx].English);
		char input1 = _getch();
		if (input1 == 'z') {
			system("color A");
		}
		else {
			system("color C");
		}
		int len_C = strlen(list[idx].Chinese);
		printf("\n\n");
		for (int i = 0; i < 26 - ((len_C + 1) >> 1); i++) {
			printf(" ");
		}
		printf("%s\n", list[idx].Chinese);
		char input2 = _getch();
		system("cls");
		system("color 7");
	}
}