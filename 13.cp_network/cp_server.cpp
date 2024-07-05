#include <iostream>
#include <conio.h>
#include <process.h>
#include <string.h>
#include <stdio.h>
using namespace std;
#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Winmm.lib")

void waitClient(void* p);
int get_file_name(SOCKET, char* );
int get_file_content(SOCKET, char* );

#define			ServerPort					4100	//port
#define			BUFFERSIZE					100	

typedef struct {
	SOCKET  skt;
	int* flag_addr;
}SOCKETP;

int main(int argc, char* argv[])
{
	WSADATA	WsaData;

	SOCKET sck;
	SOCKADDR_IN sa;

	if (0 != WSAStartup(MAKEWORD(1, 1), &WsaData)) {
		WSACleanup();
		exit(0);
	}

	sck = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sck) {
		WSACleanup();
		exit(0);
	}

	sa.sin_family = AF_INET;
	sa.sin_port = htons(ServerPort);
	sa.sin_addr.s_addr = INADDR_ANY;
	if (SOCKET_ERROR == bind(sck, (LPSOCKADDR)&sa, sizeof(sa))) {
		closesocket(sck);
		WSACleanup();
		exit(0);
	}
	
	if (SOCKET_ERROR == listen(sck, 1)) {
		closesocket(sck);
		WSACleanup();
		exit(0);
	}

	cout << "Server succeded!" << endl;
	cout << "Waiting for new client..." << endl;

	_beginthread(waitClient, 0, (void*)&sck);
	while (1) {
		Sleep(1000);
	}
	cout << "Server exiting..."<<endl;
	closesocket(sck);
	WSACleanup();
	system("pause");
	return 0;
}

void waitClient(void* p) {
	SOCKADDR_IN addrClient;
	int addrClientLen = sizeof(addrClient);
	SOCKET sck = *((SOCKET*)p);
	SOCKET ClientSocket;

	ClientSocket = accept(sck, (sockaddr FAR*) & addrClient, &addrClientLen);

	_beginthread(waitClient, 0, (void*)&sck);

	char ClientIP[21];
	strcpy_s(ClientIP, 20, inet_ntoa(addrClient.sin_addr));
	u_short ClientPort = ntohs(addrClient.sin_port);
	printf("\nAccept a client. [%s:%d]\n", ClientIP, ClientPort);

	int n;
	char buf[BUFFERSIZE + 1];
	char file_name[40];
	FILE* tfp;

	n = get_file_name(ClientSocket, file_name);
	if (n == 0) {
		printf("[%s:%d] Client disconnect!\n",ClientIP,ClientPort);
		closesocket(ClientSocket);
		return;
	}

	fopen_s(&tfp, file_name, "wb");
	if (tfp == NULL) {
		printf("[%s] is open error\n", file_name);
		closesocket(ClientSocket);
		return;
	}

	do {
		n = get_file_content(ClientSocket, buf);
		fwrite(buf, sizeof(unsigned char), n, tfp);
		if (n != 100)
			break;
	} while (1);

	fclose(tfp);
	printf("Recieve[%s] Complete...\n", file_name);
	closesocket(ClientSocket);
}

int get_file_name(SOCKET ClientSocket, char* file_name) {
	int rVal;
	char buf[BUFFERSIZE + 1];
	rVal = recv(ClientSocket, buf, BUFFERSIZE, 0);
	if (rVal > 0) {
		strcpy_s(file_name, 40, buf);
		strcpy_s(buf, 100, "OK");
		rVal = send(ClientSocket, buf, BUFFERSIZE, 0);
	}
	return rVal;
}

int get_file_content(SOCKET ClientSocket, char* buf) {
	int rVal;
	rVal = recv(ClientSocket, buf, BUFFERSIZE, 0);
	return rVal;
}