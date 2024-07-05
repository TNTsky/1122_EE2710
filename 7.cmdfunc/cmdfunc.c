#include "comandInterpreter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv)
{
    do{
        char cmd[100];

        if (argc > 1)
            strcpy_s(cmd, 100, argv[1]);
        else
        {
            printf(">> ");
            gets(cmd);
        }
        if (!cmdInterpreter(cmd))
            printf("Cmd not found \n");
    } while (1);

    
}