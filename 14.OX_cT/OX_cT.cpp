#include <stdio.h>
#include <windows.h>



char sb[3][3] = { 0x20,0x20, 0x20,
                 0x20, 0x20, 0x20,
                 0x20, 0x20, 0x20 };

//===========================================================
// Set current cursor position.
void GotoXY(SHORT x, SHORT y)
{
    // Set the cursor position.
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cord;
    Cord.X = x;
    Cord.Y = y;
    SetConsoleCursorPosition(StdOut, Cord);
}
void GetXY(int* x, int* y)
{
    // Set the cursor position.
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo = { 0 };
    GetConsoleScreenBufferInfo(StdOut, &ScreenBufferInfo);
    GetConsoleScreenBufferInfo(StdOut, &ScreenBufferInfo);
    *x = ScreenBufferInfo.dwCursorPosition.X;
    *y = ScreenBufferInfo.dwCursorPosition.Y;
}

int computerThinking2(char sbMap[3][3], int n)
{
    int i, j, cost;
    cost = sbMap[0][0] + sbMap[1][1] + sbMap[2][2];
    if (cost == n) {
        for (i = 0; i < 3; i++)
            if (sbMap[i][i] == 0)return i * 3 + i + 1;
    }
    cost = sbMap[0][2] + sbMap[1][1] + sbMap[2][0];
    if (cost == n) {
        if (sbMap[0][2] == 0)return 3;
        if (sbMap[1][1] == 0)return 5;
        if (sbMap[2][0] == 0)return 7;
    }
    for (i = 0; i < 3; i++) {
        cost = sbMap[i][0] + sbMap[i][1] + sbMap[i][2];
        if (cost == n) {
            for (j = 0; j < 3; j++)
                if (sbMap[i][j] == 0)return i * 3 + j + 1;
        }
    }
    for (i = 0; i < 3; i++) {
        cost = sbMap[0][i] + sbMap[1][i] + sbMap[2][i];
        if (cost == n) {
            for (j = 0; j < 3; j++)
                if (sbMap[j][i] == 0)return j * 3 + i + 1;
        }
    }
    return 0;
}

int computerThinking(int pos)
{
    char sbMap[3][3];
    int i, j, post;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            sbMap[i][j] = (sb[i][j] == 'O') ? 1 : ((sb[i][j] == 'X') ? -1 : 0);
    post = computerThinking2(sbMap, -2);
    if (post > 0)return post;
    post = computerThinking2(sbMap, 2);
    if (post > 0)return post;
    post = computerThinking2(sbMap, -1);
    if (post > 0)return post;
    post = computerThinking2(sbMap, 1);
    if (post > 0)return post;
    return(pos == 9) ? 1 : pos + 1;
}



void print_form(void)
{
    char* p;
    const char* frm[] = {
    " %c  | %c  | %c  \n",
    "----+----+----\n",
    " %c  | %c  | %c  \n",
    "----+----+----\n",
    " %c  | %c  | %c  \n" };
    int i, k = 0;
    int x, y, x0 = 6, y0 = 6;
    GetXY(&x, &y);
    p = (char*)sb;
    for (i = 0; i < 5; i++) {
        GotoXY(x0, y0 + i + 5);
        if (!(i % 2)) {
            printf(frm[i], ((p[k] == 0x20) ? '0' + k + 1 : p[k]),
                ((p[k + 1] == 0x20) ? '0' + k + 2 : p[k + 1]),
                ((p[k + 2] == 0x20) ? '0' + k + 3 : p[k + 2]));
            k += 3;
        }
        else {
            printf(frm[i]);
        }
    }
    GotoXY(x, y);
}

int sb_check(char turn)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (sb[i][0] == sb[i][1] && sb[i][1] == sb[i][2] &&
            sb[i][0] == turn)return 1;
    }
    for (i = 0; i < 3; i++)
    {
        if (sb[0][i] == sb[1][i] && sb[1][i] == sb[2][i] &&
            sb[0][i] == turn)return 1;
    }
    if (sb[0][0] == sb[1][1] && sb[1][1] == sb[2][2] &&
        sb[0][0] == turn)return 1;
    if (sb[2][0] == sb[1][1] && sb[1][1] == sb[0][2] &&
        sb[0][2] == turn)return 1;
    return 0;
}

int main()
{
    char turn='O';
    int pos,n=1;
    print_form();
    do {
        char *p= (char*)sb;
        if (n & 1)
        {
            turn = 'O';
            printf("[%c]>>", turn);
            scanf_s("%d", &pos);
            p[pos - 1] = 'O';
        }
        else
        {
            turn = 'X';
            int cThinking = computerThinking(n) - 1;
            p[cThinking]=turn;
        }
        print_form();
        if (sb_check(turn)) {
            printf("Winner is [%c]!!!\n", turn);
            break;
        }
        n++;
    } while (n < 9);
}
