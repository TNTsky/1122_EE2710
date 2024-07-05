#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"poker.h"

void work(PKCARD* s, int n, int* num);
void test(PKCARD* s, int n, int* num);
void check(PKCARD* s, int n, int* num);

int main()
{
    srand(time(NULL));
    int n = 13;
    PKCARD* card = (PKCARD*)malloc(n * sizeof(PKCARD));
    int* num = (int*)malloc(n * sizeof(int));

    // 測試用
    // test(card, n, num);

    do {
        GetPKCard(card, n);
        work(card, n, num);
    } while (getchar());
}

// 測試用
void test(PKCARD* s, int n, int* num) {
    int i, j;
    for (i = 1; i < 5; i++) {
        for (j = 0; j < 13; j++) {
            s[j].v = j * i;
        }
        work(s, n, num);
        puts("");
    }
    getchar();
}

void work(PKCARD* s, int n, int* num) {
    bbSort(s, n);
    printPKCard(s, n);
    count(s, n, num);
    check(s, n, num);
}

void check(PKCARD* s, int n, int* num) {
    if (is_Dragon(num)) return;
    while (is_Straight(s, n, num));
    while (is_Four_of_a_kind(s, n, num));
    while (is_Full_house(s, n, num));
    while (is_Pair(s, n, num));
}