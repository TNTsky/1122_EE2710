#include"longstr.png"
#include<stdio.h>

struct Node* getBufNode(void) {
	struct Node* buf;
	buf = (struct Node*)malloc(1 * sizeof(struct Node));
	if (buf != NULL)buf->front = buf->next = NULL;
	return buf;
}

struct Node* addBuf(struct Node* buf, int* n, char c) {
	buf->data[(*n)++] = c;
	if (*n == 100) {
		struct Node* temp = buf->next = getBufNode();
		temp->front = buf;
		*n = 0;
		return temp;
	}
	return buf;
}

char BufChar(struct Node* buf, int i) {
	return '?';
}

struct Node* decBufIndex(struct Node* buf, int* k) {
	return buf;
}

struct Node* incBufIndex(struct Node* buf, int* k) {
	return buf;
}

struct Node* delBufChar(struct Node* buft, int* k) {
	if (*k == 0) {
		buft = buft->front;
		free(buft->next);
		*k = 99;
		return buft;
	}
	(*k) -= 1;
	return buft;
}

void printbuf(struct Node* buf_head) {
	int i = 0;
	char c;
	while (c = buf_head->data[i++]) {
		putchar(c);
		if (i == 100) {
			buf_head = buf_head->next;
			i = 0;
		}
	}
}
