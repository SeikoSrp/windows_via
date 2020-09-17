// windows_via_7.11_Affinity.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include "sysinfoapi.h"

using namespace std;

void GetCPUNum() {
    SYSTEM_INFO t_system_info;
    GetSystemInfo(&t_system_info);
    cout << "CPU Num :" << t_system_info.dwNumberOfProcessors << endl;
}


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


int main()
{
    std::cout << "Hello World!\n";
    
    HANDLE hThread;

    int n = 10;
    hThread = CreateThread(NULL, 0, testThreadProc, &n, 0, NULL);//testThreadProc是函数名，&n是变量的地址
    SetThreadAffinityMask(hThread, 0x00000005);
    CloseHandle(hThread);
    Sleep(100000);
}

