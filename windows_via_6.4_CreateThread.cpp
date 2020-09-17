// th1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "windows.h"

DWORD WINAPI testThreadProc(LPVOID lpParameter)
{
    int* p = (int*)lpParameter;//将lpParameter参数转换为int*类型的
    for (int i = 0; i < *p; i++)
    {
        Sleep(500);
        printf("++++++++++++++++++++%d \n", i);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    HANDLE hThread;

    int n = 10;
    hThread = CreateThread(NULL, 0, testThreadProc, &n, 0, NULL);//testThreadProc是函数名，&n是变量的地址
    CloseHandle(hThread);
    return 0;
}