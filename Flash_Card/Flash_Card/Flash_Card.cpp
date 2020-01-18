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
void select_mode();
void flash();
void mc();

int main()
{
	readfile();
	select_mode();
}
void select_mode() {
	printf("\n\t       Flash Card (%d words)\n",count_lines);
	printf("\t\t  Developed by RW\n\n");
	printf("\ta: random words\n");
	printf("\ts: multiple choices\n");
	char input1 = _getch();
	if (input1 == 'a') {
		system("cls");
		flash();
	}
	else {
		system("cls");
		mc();
	}
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
		if (input1 == 'a') {
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

void mc() {
	srand((unsigned)time(NULL));
	while (1) {
		int idx = rand() % count_lines;
		int len_E = strlen(list[idx].English);
		printf("\n\n");
		for (int i = 0; i < 26 - ((len_E + 1) >> 1); i++) {
			printf(" ");
		}
		printf("%s\n\n", list[idx].English);
		int a, b, c, d, e, f, g;
		do {
			a = rand() % count_lines;
			b = rand() % count_lines;
			c = rand() % count_lines;
			d = rand() % count_lines;
			e = rand() % count_lines;
			f = rand() % count_lines;
			g = rand() % count_lines;
		} while (a == b || a == c || a == d || a == e || a == f || a == g || b == c || b == d || b == e || b == f ||
			b == g || c == d || c == e || c == f || c == g || d == e || d == f || d == g || e == f || e == g ||
			f == g || a == idx || b == idx || c == idx || d == idx || e == idx || f == idx || g == idx);
		int position = rand() % 8;
		int ids[] = { a,b,c,d,e,f,g };
		char hints[] = {'a','s','d','f','j','k','l',';'};
		int next = 0;
		for (int i = 0; i < 8; i++) {
			if (i == position) {
				printf("\t%c: %s\n",hints[i],list[idx].Chinese);
			}
			else {
				printf("\t%c: %s\n", hints[i], list[ids[next++]].Chinese);
			}
		}
		char input1 = _getch();
		if (input1 == hints[position]) {
			system("color A");
		}
		else {
			system("color C");
		}
		system("cls");
		printf("\n\n\n");
		for (int i = 0; i < 26 - ((len_E + 1) >> 1); i++) {
			printf(" ");
		}
		printf("%s\n", list[idx].English);
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