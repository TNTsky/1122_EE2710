#include <stdio.h>
#include <stdlib.h>

typedef int (*MathMethod)(int, int);
int Mul(int a, int b) { return a * b; }
int Divide(int a, int b) { return a / b; }
int Minus(int a, int b) { return a - b; }
int Add(int a, int b) { return a + b; }

int Calc(int x, int y, MathMethod Opt) {
    return Opt(x, y);
}

int(*calcArray[])(int, int) = {
    Mul,     // 這邊亦可以打&Mul，&可省略
    Divide,
    Add,
    Minus
};

int main() {
    int a = 8, b = 7;
    printf("a=%d, b=%d\n", a, b);
    printf("a x b = %d\n", Calc(a, b, test));
    printf("a x b = %d\n", Calc(a, b, Mul));
    printf("a / b = %d\n", Calc(a, b, Divide));
    printf("a + b = %d\n", Calc(a, b, Add));
    printf("a - b = %d\n", Calc(a, b, Minus));
    puts("----------------");
    printf("a x b = %d\n", calcArray[0](a, b));
    printf("a / b = %d\n", calcArray[1](a, b));
    printf("a + b = %d\n", calcArray[2](a, b));
    printf("a - b = %d\n", calcArray[3](a, b));
    return 0;
}

