#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

unsigned long int next = 1;

void srand(double seed) {
	next = seed;
}

int rand(int min, int max) {
	next = next * 48271 + 0;
	return (unsigned int)(next / 65536) % (max - min + 1) + min;
}
char alphabet[3][32];

int main() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	srand(time(0));

	for (char i = 'A'; i <= 'Z'; alphabet[0][i - 'A'] = i++);
	for (char i = 'a'; i <= 'z'; alphabet[1][i - 'a'] = i++);
	for (char i = '0'; i <= '9'; alphabet[2][i - '0'] = i++);

	printf("%s\n", alphabet[0]);
	printf("%s\n", alphabet[1]);
	printf("%s\n", alphabet[2]);

	printf("Enter the desired lenght of password to generate\n> ");
	int lenght = 16;
	scanf("%d", &lenght);

	for (int j, i = 0; i < lenght; i++) {
		j = rand(0, 2);
		printf("\033[%dm%c\033[0m", 91+j, alphabet[j][rand(0, strlen(alphabet[j] + 1))]);
	}
}