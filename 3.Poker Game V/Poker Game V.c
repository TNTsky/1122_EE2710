#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define U8 unsigned char

// char* cardType[] = { "♣","♦","♥","♠" };
char* cardType[] = { "Club","Diamond","Heart","Spade" };
char* cardNo[] = { "A","2","3","4","5" ,"6" ,"7" ,"8" ,"9" ,"10" ,"J" ,"Q" ,"K" };

typedef union{
	 struct {
	 unsigned CardType : 2;
	 unsigned CardNo : 6;
	 };
	 U8 v;
}PKCARD;

void GetPKCard(PKCARD *s);
int issame(PKCARD *s, int i);
void swap(PKCARD *a, PKCARD *b);
void bbSort(PKCARD *s);
void printPKCard(PKCARD *s);
void check(PKCARD *s);

int is_Straight_flush(PKCARD *s); // 同花順
int is_Four_of_a_kind(PKCARD *s); // 四條
int is_Full_house(PKCARD *s); // 葫蘆
int is_Flush(PKCARD *s, int n); // 同花
int is_Straight(PKCARD *s); // 順子
int is_Three_of_a_kind(PKCARD *s, int n); // 三條
int is_Two_pair(PKCARD *s); // 兩對
int is_Pair(PKCARD *s); // 對子



int main(void) {
	srand(time(NULL));
	PKCARD card[5];
	do {
		GetPKCard(card);
		bbSort(card);
		printPKCard(card);
		check(card);
	} while (getchar());
}


void GetPKCard(PKCARD *s) {
	int t = 0;
	while (t < 5) {
		char c = rand() % 52;
		s[t].v = c;
		if (issame(s, t))
			continue;
		t++;
	}
}

int issame(PKCARD *s, int t) {
	int i;
	for (i = 0; i < t; i++)
		if (s[i].v == s[t].v)
			return 1;
	return 0;
}

void swap(PKCARD * a, PKCARD * b) {
	PKCARD t = *a;
	*a = *b;
	*b = t;
}

void bbSort(PKCARD *s) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4 - i; j++) {
			if (s[j].v > s[j + 1].v) {
				swap(s + j, s + j + 1);
			}
		}
	}
}

void printPKCard(PKCARD *s) {
	int i;
	for (i = 0; i < 5; i++) {
		int type = s[i].CardType;
		int num = s[i].CardNo;
		printf("[%7s,%2s]\t", cardType[type], cardNo[num]);
	}
}

void check(PKCARD *s) {
	if (is_Straight_flush(s)) {
		puts(" Straight flush (同花順)");
		return;
	}
	else if (is_Four_of_a_kind(s)) {
		puts(" Four_of_a_kind (四條)");
		return;
	}
	else if (is_Full_house(s)) {
		puts(" Full house (葫蘆)");
		return;
	}
	else if (is_Flush(s, 1)) {
		puts(" Flush (同花)");
		return;
	}
	else if (is_Straight(s)) {
		puts(" Straight (順子)");
		return;
	}
	else if (is_Three_of_a_kind(s, 1)) {
		puts(" Three of a kind (三條)");
		return;
	}
	else if (is_Two_pair(s)) {
		puts(" Two_pair (兩對)");
		return;
	}
	else if (is_Pair(s)) {
		puts(" Pair (對子)");
		return;
	}
	printf("%s", cardNo[s[4].CardNo]);
	puts(" High card (單牌)");
}

// 同花順
int is_Straight_flush(PKCARD *s) {
	if (is_Flush(s, 0)) {
		if (is_Straight(s)) {
			printf("%s", cardType[s[0].CardType]);
			printf("%s", cardNo[s[4].CardNo]);
			return 1;
		}
	}
	return 0;
}

// 四條
int is_Four_of_a_kind(PKCARD *s) {
	int i, count = 0;
	for (i = 0; i < 5; i++)
		if ((s[2].CardNo) == (s[i]).CardNo)
			count++;
	if (count == 4) {
		printf("%s", cardNo[s[2].CardNo]);
		return 1;
	}
	return 0;
}

// 葫蘆
int is_Full_house(PKCARD *s) {
	if (is_Three_of_a_kind(s, 0)) {
		if (((s[0].CardNo) == (s[1].CardNo)) && ((s[3].CardNo) == (s[4].CardNo))) {
			printf("%s", cardNo[s[2].CardNo]);
			return 1;
		}
	}
	return 0;
}

// 同花
int is_Flush(PKCARD *s, int n) {
	int i;
	for (i = 1; i < 5; i++)
		if ((s[0].CardType) != (s[i].CardType))
			return 0;
	if (n)
		printf("%s", cardType[s[0].CardType]);
	return 1;
}

// 順子
int is_Straight(PKCARD *s) {
	int i;
	for (i = 0; i < 4; i++)
		if (((s[i].CardNo + 1)) != (s[i + 1].CardNo))
			return 0;
	printf("%s", cardNo[s[4].CardNo]);
	return 1;
}

// 三條
int is_Three_of_a_kind(PKCARD *s, int n) {
	int i, count = 0;
	for (i = 0; i < 5; i++)
		if ((s[2].CardNo) == (s[i]).CardNo)
			count++;
	if (count == 3) {
		if (n)
			printf("%s", cardNo[s[2].CardNo]);
		return 1;
	}
	return 0;
}

// 兩對
int is_Two_pair(PKCARD *s) {
	int i, count = 0, a = -1, b = -1;
	for (i = 0; i < 4; i++) {
		if ((s[i].CardNo) == (s[i + 1].CardNo)) {
			if (a >= 0)
				b = (s[i].CardNo);
			else
				a = (s[i].CardNo);
			count++;
		}
	}
	if (count == 2) {
		printf("%s, %s", cardNo[a], cardNo[b]);
		return 1;
	}
	return 0;
}

// 對子
int is_Pair(PKCARD *s) {
	int i, count = 0, a = 0;
	for (i = 0; i < 4; i++) {
		if ((s[i].CardNo) == (s[i + 1]).CardNo) {
			a = s[i].CardNo;
			count++;
		}
	}
	if (count == 1) {
		printf("%s", cardNo[a]);
		return 1;
	}
	return 0;
}
