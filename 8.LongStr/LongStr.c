#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int main(void) {
	char* str = (char*)malloc(sizeof(char) * 100 + sizeof(char*));
	while (1) {
		char c, * start = str;
		int i = 0;
		while ((c = _getch()) != 0x1b) {
			if (c == '\r')
				c = '\n';
			putchar(c);
			if (i == 100) {
				i = 0;
				str = *((char**)&str[100]) = (char*)malloc(sizeof(char) * 100 + sizeof(char*));
			}
			str[i++] = c;
		}
		puts("\n-----------------------------------------------------------------");
		str[i] = 0x00;
		i = 0;
		str = start;
		while (str[i]) {
			putchar(str[i++]);
			if (i == 100) {
				str = *((char**)&str[i]);
				i = 0;
			}
		}
		puts("\n============================================================");
	}
}