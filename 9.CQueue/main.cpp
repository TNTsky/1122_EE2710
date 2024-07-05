#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <process.h>
#include <windows.h>
using namespace std;
#include <conio.h>
#include "CQueue.h"

HANDLE init_rs232();
void COMSend(HANDLE hComm, char vOutData[], unsigned long BS);
DWORD COMRecv(HANDLE hComm, char* inbuff);
unsigned __stdcall RecvData(void*);
unsigned __stdcall KeyData(void*);
void getLocalTimeLog(char* cctime);
void putsXY(char* s, int x, int y); // 假设 putsXY 函数已定义
CQueue cqUart, cqKIn;

int main(void)
{
    char c = 0x00;
    HANDLE hComm;
    char buf[100], cctime[40], cmd[100];
    int i;

    CQ_init(&cqUart);

    hComm = init_rs232();
    printf("[%p]", hComm);
    _beginthreadex(NULL, 0, RecvData, (void*)&hComm, 0, NULL);
    _beginthreadex(NULL, 0, KeyData, NULL, 0, NULL);
    i = 0;
    while (1)
    {
        while (!isCQempty(&cqKIn)) {
            c = deletCQ(&cqKIn);
            putchar(c);
            if (c == 0x0D) {
                cmd[i] = 0x0D;
                putchar(0x0A);
            }
            else {
                cmd[i++] = c;
            }
        }
        if (i != 0) {
            if (cmd[i] == 0x0D) {
                cmd[i] = 0x00;
                COMSend(hComm, cmd, i);
                i = 0;
            }
        }

        if (!isCQempty(&cqUart)) {
            c = deletCQ(&cqUart);
            putchar(c);
        }

        getLocalTimeLog(cctime);
        sprintf_s(buf, 100, "%s  ", cctime);
        putsXY(buf, 60, 1);

        Sleep(1);
    }
    getchar();
}

void getLocalTimeLog(char* cctime)
{
    time_t timer;
    struct tm tblock;

    timer = time(NULL);
    localtime_s(&tblock, &timer);
    sprintf_s(cctime, 100, "%d/%02d/%02d[%02d] %02d:%02d:%02d", (tblock.tm_year + 1900) - 1911, tblock.tm_mon + 1, tblock.tm_mday, tblock.tm_wday, tblock.tm_hour, tblock.tm_min, tblock.tm_sec);
}

unsigned __stdcall RecvData(void* p)
{
    char c;
    int n;
    HANDLE hComm = *(HANDLE*)p; // 从参数中获取 hComm 的值

    while (1) {
        n = COMRecv(hComm, &c);
        if (n == 1)
            insertCQ(&cqUart, c);
    }
    return 0;
}

unsigned __stdcall KeyData(void*)
{
    char c;
    while (1) {
        c = _getch();
        insertCQ(&cqKIn, c);
    }
    return 0;
}

HANDLE init_rs232()
{
    DCB dcb;
    HANDLE hComm;
    char c;

    hComm = CreateFileA("\\\\.\\COM5", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

    if (hComm == INVALID_HANDLE_VALUE)
    {
        cout << "開啟通訊埠錯誤!" << endl;
        system("pause");
        return 0;
    }

    FillMemory(&dcb, sizeof(dcb), 0);

    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fBinary = TRUE;

    dcb.fRtsControl = RTS_CONTROL_TOGGLE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fTXContinueOnXoff = FALSE;
    dcb.fOutX = FALSE;
    dcb.fInX = FALSE;
    dcb.fErrorChar = FALSE;
    dcb.fNull = FALSE;
    dcb.fAbortOnError = FALSE;

    if (!SetCommState(hComm, &dcb))
    {
        CloseHandle(hComm);
        cout << "通訊埠設定錯誤!" << endl;
        return 0;
    }

    COMMTIMEOUTS tTimeout;
    GetCommTimeouts(hComm, &tTimeout);
    tTimeout.ReadIntervalTimeout = 1;
    tTimeout.ReadTotalTimeoutMultiplier = 1;
    tTimeout.ReadTotalTimeoutConstant = 1;
    SetCommTimeouts(hComm, &tTimeout);

    COMRecv(hComm, &c);

    return hComm;
}

void COMSend(HANDLE hComm, char vOutData[], unsigned long BS)
{
    unsigned long lrc;

    if (hComm == 0) return;

    WriteFile(hComm, vOutData, BS, &lrc, NULL);
}

void COMSendStr(HANDLE hComm, char vOutData[], unsigned long BS)
{
    unsigned long lrc;

    if (hComm == 0) return;

    WriteFile(hComm, vOutData, BS, &lrc, NULL);
}

DWORD COMRecv(HANDLE hComm, char* inbuff)
{
    DWORD byteRead, errCode;
    COMSTAT state;

    ClearCommError(hComm, &errCode, &state);

    ReadFile(hComm, inbuff, 1, &byteRead, NULL);

    return byteRead;
}

//=====================================================================
// Set current cursor position.
void GotoXY(int x, int y)
{
    // Set the cursor position.
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cord;
    Cord.X = x;
    Cord.Y = y;
    SetConsoleCursorPosition(StdOut, Cord);
}
void GetXY(int* x, int* y) {
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
    memset(&ScreenBufferInfo, 0, sizeof(CONSOLE_SCREEN_BUFFER_INFO));
    ScreenBufferInfo.dwSize.X = 120;
    ScreenBufferInfo.dwSize.Y = 30;
    ScreenBufferInfo.dwCursorPosition.X = 0;
    ScreenBufferInfo.dwCursorPosition.Y = 0;
    ScreenBufferInfo.wAttributes = 0;
    ScreenBufferInfo.srWindow.Left = 0;
    ScreenBufferInfo.srWindow.Right = 119;
    ScreenBufferInfo.srWindow.Top = 0;
    ScreenBufferInfo.srWindow.Bottom = 29;
    ScreenBufferInfo.dwMaximumWindowSize.X = 120;
    ScreenBufferInfo.dwMaximumWindowSize.Y = 30;

    GetConsoleScreenBufferInfo(StdOut, &ScreenBufferInfo);

    *x = ScreenBufferInfo.dwCursorPosition.X;
    *y = ScreenBufferInfo.dwCursorPosition.Y;
}
void putsXY(char* s, int x, int y)
{
    int xt, yt;

    GetXY(&xt, &yt);
    GotoXY(x, y);
    printf("%s  ", s);
    GotoXY(xt, yt);
}