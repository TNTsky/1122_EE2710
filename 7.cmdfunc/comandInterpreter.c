#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static void login(void* p);
static void hello(void* p);
static void goodbye(void* p);
static void cls(void* p);
static void EXIT();

typedef struct
{
    const char* cmdname;
    void (*f)(void*);
}CmdTBL;

static CmdTBL CT[] =
{
    {"CMD1", hello},
    {"CMD2", goodbye},
    {"cls", cls},
    {"EXIT", EXIT},
    {"Hello!", login},
    {NULL, NULL}
};

int cmdInterpreter(char* cmd)
{
    int i, k; char c = 0x00;

    for (i = 0; cmd[i] && cmd[i] != ' '; i++);

    if (cmd[i] == ' ')
    {
        c = ' ';
        cmd[i] = 0x00;
    }

    for (k = 0; CT[k].cmdname != NULL; k++)
    {
        if (!strcmp(cmd, CT[k].cmdname))
        {
            cmd[i] = c;
            CT[k].f(cmd);
            return 1;
        }
    }
    return 0;
}

void login(void* p)
{
    char* s;
    s = (char*)p;
    printf("login[%s]\n", s);
}

void hello(void* p)
{
    char* s;
    s = (char*)p;
    printf("hello[%s]\n", s);
}

void goodbye(void* p)
{
    char* s;
    s = (char*)p;
    printf("goodbye[%s]\n", s);
}

void cls(void* p)
{
    char* s;
    s = (char*)p;
    printf("cls[%s]\n", s);
}

void EXIT()
{
    exit(0);
}