#include<stdio.h>
#include<stdlib.h>

int main(void) {
    char* str = (char*)malloc(sizeof(char) * 100 + sizeof(char*));
    int i = 1;
    while (i++) {
        printf("已使用 %d M\n", i);
        str = *((char**)&str[1]) = (char*)malloc(sizeof(char) * 1000000 + sizeof(char*));
    }
}