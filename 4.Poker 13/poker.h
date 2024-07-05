#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define U8 unsigned char

const char* cardType[] = { "C","D","H","S" };
const char* cardNo[] = { "A","2","3","4","5" ,"6" ,"7" ,"8" ,"9" ,"10" ,"J" ,"Q" ,"K" };

typedef union {
    struct {
        unsigned CardType : 2;
        unsigned CardNo : 5;
        unsigned Used : 1;
    };
    U8 v;
}PKCARD;

void GetPKCard(PKCARD* s, int n);
int issame(PKCARD* s, int t);
void swap(PKCARD* a, PKCARD* b);
void bbSort(PKCARD* s, int n);
void printPKCard(PKCARD* s, int n);
void count(PKCARD* s, int n, int* num);

int is_Dragon(int* num); // 一條龍
int is_Straight_flush(PKCARD* s, int n, int* num); // 同花順
int is_Four_of_a_kind(PKCARD* s, int n, int* num); // 鐵支
int is_Full_house(PKCARD* s, int n, int* num); // 葫蘆
int is_Flush(PKCARD* s, int n, int* num, int o); // 同花
int is_Straight(PKCARD* s, int n, int* num); // 順子
int is_Three_of_a_kind(PKCARD* s, int n, int* num, int o); // 三條
int is_Two_pair(PKCARD* s, int n, int* num); // 兩對
int is_Pair(PKCARD* s, int n, int* num); // 對子


void GetPKCard(PKCARD* s, int n) {
    int t = 0;
    while (t < n) {
        char c = rand() % 52;
        s[t].v = c;
        if (issame(s, t))
            continue;
        t++;
    }
}

int issame(PKCARD* s, int t) {
    int i;
    for (i = 0; i < t; i++)
        if (s[i].v == s[t].v)
            return 1;
    return 0;
}

void swap(PKCARD* a, PKCARD* b) {
    PKCARD t = *a;
    *a = *b;
    *b = t;
}

void bbSort(PKCARD* s, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (s[j].v > s[j + 1].v) {
                swap(s + j, s + j + 1);
            }
        }
    }
}

void printPKCard(PKCARD* s, int n) {
    int i;
    for (i = 0; i < n; i++) {
        int type = s[i].CardType;
        int num = s[i].CardNo;
        printf("%s%-2s ", cardType[type], cardNo[num]);
    }
}

void count(PKCARD* s, int n, int* num) {
    memset(num, 0, n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
        num[s[i].CardNo]++;
}


int is_Dragon(int* num) {
    int i;
    for (i = 0; i < 13; i++) {
        if (num[i] != 1)
            return 0;
    }
    printf("  一條龍!!!");
    return 1;
}

int is_Straight(PKCARD* s, int n, int* num) {
    int i, j, count = 0, find = 0, biggest = 0;
    for (i = 12; i >= 0; i--) {
        if (num[i]) count++;
        else count = 0;
        if (count == 5) {
            find = 1;
            biggest = i + 4;
            break;
        }
    }
    if (!find) {
        return 0;
    }
    for (i = biggest; i > biggest - 5; i--)
        num[i]--;
    int type[4] = { 0 };
    for (i = 0; i < 13; i++) {
        if (s[i].Used != 1 && s[i].CardNo > biggest - 5 && s[i].CardNo <= biggest) {
            if (++type[s[i].CardType] == 5) {
                printf("  同花順%s[", cardType[s[i].CardType]);
                for (j = biggest - 4; j <= biggest; j++)
                    printf("%s", cardNo[j]);
                printf("]");
                int del = 5, ty = s[i].CardType;
                while (del > 0) {
                    if (s[i].CardType == ty) {
                        s[i].Used = 1;
                        del--;
                    }
                    i--;
                }
                return 1;
            }
        }
    }
    int nowdel = biggest - 4, del = 5;
    for (i = 0; i < 13; i++) {
        if (s[i].Used != 1 && s[i].CardNo == nowdel) {
            s[i].Used = 1;
            nowdel++;
            del--;
        }
        if (del == 0)
            break;
    }
    printf("  順子[");
    for (j = biggest - 4; j <= biggest; j++)
        printf("%s", cardNo[j]);
    printf("]");
    return 1;
}

int is_Four_of_a_kind(PKCARD* s, int n, int* num) {
    int i, j, no, find = 0;
    for (i = 12; i >= 0; i--) {
        if (num[i] == 4) {
            no = i;
            find = 1;
            break;
        }
    }
    if (!find) return 0;
    for (i = 0; i < 13; i++) {
        if (s[i].CardNo == no)
            s[i].Used = 1;
    }
    num[no] = 0;
    int del = 1, wantdel = 1;
    while (del) {
        for (i = 0; i < 13; i++) {
            if (num[s[i].CardNo] == wantdel && s[i].Used != 1) {
                num[s[i].CardNo]--;
                s[i].Used = 1;
                del--;
                printf("  鐵支[%s%s%s%s%s]", cardNo[no], cardNo[no], cardNo[no], cardNo[no], cardNo[s[i].CardNo]);
                return 1;
            }
        }
        if (++wantdel > 5)
            break;
    }
    printf("  四條[%s%s%s%s]", cardNo[no], cardNo[no], cardNo[no], cardNo[no]);
    return 1;
}

int is_Full_house(PKCARD* s, int n, int* num) {
    int i, j, no, find = 0;
    for (i = 12; i >= 0; i--) {
        if (num[i] == 3) {
            no = i;
            find = 1;
            break;
        }
    }
    if (!find) return 0;
    for (i = 0; i < 13; i++) {
        if (s[i].CardNo == no && s[i].Used != 1)
            s[i].Used = 1;
    }
    num[no] = 0;
    int del = 2, wantdel = 2;
    while (del) {
        for (i = 0; i < 13; i++) {
            if (num[s[i].CardNo] == wantdel && s[i].Used != 1) {
                num[s[i].CardNo]--;
                s[i].Used = 1;
                del--;
                if (del == 0) {
                    printf("  葫蘆[%s%s%s%s%s]", cardNo[no], cardNo[no], cardNo[no], cardNo[s[i].CardNo], cardNo[s[i].CardNo]);
                    return 1;
                }
            }
        }
        if (++wantdel > 4)
            break;
    }
    printf("  三條[%s%s%s]", cardNo[no], cardNo[no], cardNo[no]);
    return 1;

}

int is_Pair(PKCARD* s, int n, int* num) {
    int i, j, no, find = 0;
    for (i = 12; i >= 0; i--) {
        if (num[i] == 2) {
            no = i;
            find = 1;
            break;
        }
    }
    if (!find) return 0;
    for (i = 0; i < 13; i++) {
        if (s[i].CardNo == no && s[i].Used != 1)
            s[i].Used = 1;
    }
    num[no] = 0;
    printf("  一對[%s%s]", cardNo[no], cardNo[no]);
    return 1;
}