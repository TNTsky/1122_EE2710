#include <stdio.h>
#include <stdlib.h>

int f(int x) {
    if (x <= 0) return x;
    else if (x == 1) return 1;
    return f(x - 2) + f(x - 1);
}

int dp[100] = { 0 }; 
int ff(int x) {
    if (x <= 0) return x;
    else if (dp[x]) return dp[x];
    dp[x] = ff(x - 2) + ff(x - 1);
    return dp[x];
}

int main(void) {
    int n;
    dp[1] = 1; dp[2] = 1;
    while (1) {
        printf("Enter a num: ");
        scanf_s("%d", &n);
        printf("%d\n\n", f(n));
    }
    return 0;
}
