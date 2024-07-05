#include"longstr.png"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int main(void) {
	while (1) {
		struct Node* buf = getBufNode();
		struct Node* head = buf;
		char c;
		int i = 0;

		while ((c = _getch()) != 0x1b){
			switch (c){
			case 0x0d:  // Enter
				c = 0x0a;
				buf = addBuf(buf, &i, c);
				putchar(c);
				break;
			case 0x08:  // Backspace
				buf = delBufChar(buf, &i);
				putchar(c);
				putchar(' ');
				putchar(c);
				break;
			default:
				buf = addBuf(buf, &i, c);
				putchar(c);
				break;
			}
		}
		buf->data[i] = 0x00;
		puts("\n------------------------------------------");
		printbuf(head);
		puts("\n==========================================");
	}
	return 0;
}