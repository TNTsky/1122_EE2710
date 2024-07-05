#include <iostream>
#include <conio.h>
#include <string.h>
#include <process.h>
#include <stdio.h>

using namespace std;

#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")

#define			ServerIP					"127.0.0.1"	//port
#define			ServerPort					4100	//port
#define			BUFFERSIZE					100		//每次接受或傳送的緩衝大小

WSADATA			WsaData;
SOCKET          ServerSocket;

void	connectServer(void);
int send_file_name(void);
int send_file_content(int n, char* buf);

typedef struct {
    SOCKET skt;
    int* flag_addr;
}SOCKETP;

char file_name[40];


int main(int argc,char* argv[])
{
    if (argc != 2) {
        printf("Please use %s <file_name>\n", argv[0]);
        system("pause");
        return 0;
    }
    strcpy_s(file_name, 40, argv[1]);
    if (0 != WSAStartup(MAKEWORD(1, 1), &WsaData))
        exit(0);

    connectServer();

    WSACleanup();
    puts("");
    return 0;
}

void connectServer(void) {
    char buf[BUFFERSIZE];
    sockaddr_in ServerAddr;

    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == ServerSocket) {
        return;
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(ServerIP);
    ServerAddr.sin_port = htons(ServerPort);
    if (SOCKET_ERROR == connect(ServerSocket,(LPSOCKADDR)&ServerAddr,sizeof(ServerAddr))) {
        printf("Connect Error!\n");
        closesocket(ServerSocket);
        return;
    }

    printf("Connect Success!\n");

    FILE* sfp;
    int n;

    fopen_s(&sfp, file_name, "rb");
    if (sfp == NULL) {
        printf("[%s] is open error!\n", file_name);
        return;
    }

    send_file_name();

    do {
        n = fread(buf, sizeof(unsigned char), 100, sfp);
        send_file_content(n, buf);
        if (n != 100) {
            break;
        }
    } while (1);

    fclose(sfp);

    printf("Send Complete...\n");
    closesocket(ServerSocket);
}

int send_file_name(void) {
    int rVal;
    char buf[BUFFERSIZE + 1];
    strcpy_s(buf, BUFFERSIZE, file_name);
    rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
    rVal = recv(ServerSocket, buf, BUFFERSIZE, 0);
    if (rVal > 0) {
        if (strcmp(buf, "OK") == 0)
            return 1;
    }
    return 0;
}

int send_file_content(int n, char* buf) {
    int rVal;
    rVal = send(ServerSocket, buf, n, 0);
    return rVal;
}