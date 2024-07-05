#include <stdio.h>
#include <stdlib.h>

const char* s0[] = {
    "      ,@@.        @@*     ",
    NULL
};

const char* s1[] = {
	"      /@.              %.   ",
    NULL
};

const char* s2[] = {
	"      @@&.    @%              ",
    NULL
};

void putStrLine(char* s) {
    int i;
    for (i = 0; s[i]; i++)
        putchar(s[i]);
}

void printName(char*** Name) {
    int i, j;
    for (i , j = 0; Name[0][j]; j++) {
        for (i = 0; Name[i]; i++) {
            putStrLine(Name[i][j]);
        }
        putchar('\n');
    }
}

void printNameV(char*** Name) {
    int i , j;
    for (i = 0; Name[i]; i++) {
        for (j = 0; Name[i][j]; j++) {
            putStrLine(Name[i][j]);
            putchar('\n');
        }
        putchar('\n');
    }
}

int main(void){
	char*** Name = (char***)malloc(5 * sizeof(char**));
	Name[0] = (char**)s0;
	Name[1] = (char**)s1;
	Name[2] = (char**)s2;
    Name[3] = NULL;
    Name[4] = NULL;

    puts("printName:\n");
    printName(Name);
    puts("\n\nprintNameV:\n");
    printNameV(Name);

    free(Name);
    return 0;
}