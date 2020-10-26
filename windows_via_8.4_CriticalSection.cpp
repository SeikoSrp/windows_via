// windows_via_8.4_CriticalSection.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

using namespace std;

const int COUNT = 1000;
int g_nSum = 0;
CRITICAL_SECTION g_cs;

DWORD WINAPI FirstThread(PVOID pvParam)
{
    g_nSum = 0;
    for (int n = 1; n <= COUNT; n++)
    {
        g_nSum += n;
    }
    cout << "First:" << g_nSum << endl;
    return(g_nSum);
}

DWORD WINAPI SecondThread(PVOID pvParam)
{
    g_nSum = 0;
    for (int n = 1; n <= COUNT; n++)
    {
        g_nSum += n;
    }
    cout << "Second:" << g_nSum << endl;
    return(g_nSum);
}

//使用了关键段
DWORD WINAPI FirstThreadCS(PVOID pvParam)
{
    InitializeCriticalSection(&g_cs);//在使用EnterCriticalSection之前要初始化CriticalSection结构
    EnterCriticalSection(&g_cs);
    g_nSum = 0;
    for (int n = 1; n <= COUNT; n++)
    {
        g_nSum += n;
    }
    LeaveCriticalSection(&g_cs);
    cout << "First:" << g_nSum << endl;
    return(g_nSum);
}
//使用了关键段和旋转锁
DWORD WINAPI SecondThreadCS(PVOID pvParam)
{
    int SpinCount = 1000;
    InitializeCriticalSectionAndSpinCount(&g_cs, SpinCount);//初始化旋转锁
    EnterCriticalSection(&g_cs);
    g_nSum = 0;
    for (int n = 1; n <= COUNT; n++)
    {
        g_nSum += n;
    }
    LeaveCriticalSection(&g_cs);
    cout << "Second:" << g_nSum << endl;
    return(g_nSum);
}

int main()
{

    HANDLE hThread1;
    HANDLE hThread2;

    hThread1 = CreateThread(NULL, 0, FirstThreadCS, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, SecondThreadCS, NULL, 0, NULL);
    //如果两个线程是同时调用的EnterCriticalSection，那么一个线程会被获准访问资源，另一个会被切换到等待状态
    //也可以使用TryEnterCriticalSection

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
    
}
