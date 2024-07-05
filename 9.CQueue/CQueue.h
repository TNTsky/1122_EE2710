#pragma once
typedef struct
{
	char buf[256];
	int front, tail;
}CQueue;
void CQ_init(CQueue * p);
int isCQempty(CQueue * p);
char insertCQ(CQueue * p, char c);
char deletCQ(CQueue * p);