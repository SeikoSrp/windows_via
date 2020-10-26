// windows_via_8.1_Interlocked.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>

using namespace std;

long g_x = 0;

DWORD WINAPI ThreadFunc1(PVOID pvParam) {
    //g_x++;
    InterlockedExchangeAdd(&g_x, 1);
    return 0;
}

DWORD WINAPI ThreadFunc2(PVOID pvParam) {
    //g_x++;
    InterlockedExchangeAdd(&g_x, 1);
    return 0;
}

int main()
{
    HANDLE hThread1;
    HANDLE hThread2;

    hThread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);

    WaitForSingleObject(hThread1,INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    cout << "GX:" << g_x << endl;
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    //执行结果一直都是2，不知道是不是因为CPU能同时执行的线程过较多，没有影响到同步的问题？

    return 0;
}
