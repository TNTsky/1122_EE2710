#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// char* cardType[] = { "♣","♦","♥","♠" };
char* cardType[] = { "Club","Diamond","Heart","Spade" };
char* cardNo[] = {"1","2","3","4","5" ,"6" ,"7" ,"8" ,"9" ,"10" ,"J" ,"Q" ,"K" };

void GetPKCard(char* s);
int issame(char* s,int i);
void swap(char* a, char* b);
void bbSort(char* s);
void printPKCard(char *s);
void check(char* s);

int is_Straight_flush(char* s); // 同花順
int is_Four_of_a_kind(char* s); // 四條
int is_Full_house(char* s); // 葫蘆
int is_Flush(char* s,int n); // 同花
int is_Straight(char* s); // 順子
int is_Three_of_a_kind(char* s,int n); // 三條
int is_Two_pair(char* s); // 兩對
int is_Pair(char* s); // 對子


int main(void) {
	srand(time(NULL));
	//char card[5] = {0,1,2,3,4};
	char card[5];
	do {
		GetPKCard(card);
		bbSort(card);
		printPKCard(card);
		check(card);
	} while (getchar());
}


void GetPKCard(char* s) {
	int t = 0;
	while (t < 5) {
		char c = rand() % 52 ;
		s[t] = c;
		if (issame(s, t))
			continue;
		t++;
	}
}

int issame(char* s, int t) {
	int i;
	for (i = 0; i < t; i++)
		if (s[i] == s[t])
			return 1;
	return 0;
}

void swap(char* a, char* b) {
	char t = *a;
	*a = *b;
	*b = t;
}

void bbSort(char* s) {
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4-i; j++) {
			if (s[j] > s[j + 1]) {
				swap(s + j, s + j + 1);
			}
		}
	}
}

void printPKCard(char *s) {
	int i;
	for (i = 0; i < 5; i++) {
		int type = s[i] % 4;
		int num = s[i] >> 2;
		printf("[%7s,%2s]\t", cardType[type],cardNo[num]);
	}
}

void check(char* s) {
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
	else if (is_Flush(s,1)) {
		puts(" Flush (同花)");
		return;
	}
	else if (is_Straight(s)) {
		puts(" Straight (順子)");
		return;
	}
	else if (is_Three_of_a_kind(s,1)) {
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
	printf("%s", cardNo[s[4] >> 2]);
	puts(" High card (單牌)");
}

// 同花順
int is_Straight_flush(char* s) {
	if (is_Flush(s, 0)) {
		if (is_Straight(s)) {
			printf("%s", cardType[s[0] % 4]);
			printf("%s", cardNo[s[4] >> 2]);
			return 1;
		}
	}
	return 0;
}

// 四條
int is_Four_of_a_kind(char* s) {
	int i,count=0;
	for (i = 0; i < 5; i++)
		if ((s[2] >> 2) == (s[i])>>2)
			count++;
	if (count == 4) {
		printf("%s", cardNo[s[2] >> 2]);
		return 1;
	}
	return 0;
}

// 葫蘆
int is_Full_house(char* s) {
	if (is_Three_of_a_kind(s,0)) {
		if (((s[0] >> 2) == (s[1] >> 2)) && ((s[3] >> 2) == (s[4] >> 2))) {
			printf("%s", cardNo[s[2] >> 2]);
			return 1;
		}
	}
	return 0;
}

// 同花
int is_Flush(char* s,int n) {
	int i;
	for (i = 1; i < 5; i++)
		if ((s[0] % 4) != (s[i] % 4)) 
			return 0;
	if(n)
		printf("%s", cardType[s[0] % 4]);
	return 1;
}

// 順子
int is_Straight(char* s) {
	int i;
	for (i = 0; i < 4; i++)
		if (((s[i] + 1) >> 2) != (s[i + 1] >> 2))
			return 0;
	printf("%s", cardNo[s[4] >> 2]);
	return 1;
}

// 三條
int is_Three_of_a_kind(char* s,int n) {
	int i,count=0;
	for (i = 0; i < 5; i++)
		if ((s[2] >> 2) == (s[i]) >> 2)
			count++;
	if (count == 3) {
		if(n)
			printf("%s", cardNo[s[2] >> 2]);
		return 1;
	}
	return 0;
}

// 兩對
int is_Two_pair(char* s) {
	int i,count=0,a=-1,b=-1;
	for (i = 0; i < 4; i++) {
		if ((s[i] >> 2) == (s[i + 1] >> 2)) {
			if (a>=0)
				b = (s[i] >> 2);
			else
				a = (s[i] >> 2);
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
int is_Pair(char* s) {
	int i, count = 0,a=0;
	for (i = 0; i < 4; i++) {
		if ((s[i] >> 2) == (s[i + 1]) >> 2) {
			a = s[i] >> 2;
			count++;
		}
	}
	if (count == 1) {
		printf("%s", cardNo[a]);
		return 1;
	}
	return 0;
}
