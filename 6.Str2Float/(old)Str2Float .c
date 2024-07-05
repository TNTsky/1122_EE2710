#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void str2f(char* str);

int main(){
    char str[100];
    while ((fgets(str, 100, stdin)) != EOF) {
        str2f(str);
    }
}

void str2f(char* str) {
    char* c = str;
    if (*c == '-') printf('1');
    else printf('0');
    int up = 0,down=0,ddig=0;
    c++;
    while (!isspace(*c) && *c != '.') {
        up *= 10;
        up += (*c - '0');
        c++;
    }
    if (*c == '.')c++;
    while (!isspace(*c)) {
        ddig++;
        down *= 10;
        down += (*c - '0');
        c++;
    }
    int pow = 1;
    while ((1 << pow) & up) pow++;

    
    
}