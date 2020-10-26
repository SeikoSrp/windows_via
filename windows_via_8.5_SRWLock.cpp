// windows_via_8.5_SRWLock.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

using namespace std;

const int COUNT = 1000;
int g_nSum = 0;
SRWLOCK Srwlock;

//用上一节的函数作为例子
DWORD WINAPI FirstThread(PVOID pvParam)
{
    AcquireSRWLockExclusive(&Srwlock);//尝试获得对被保护的资源的独占访问
    g_nSum = 0;
    for (int n = 1; n <= COUNT; n++)
    {
        g_nSum += n;
    }
    ReleaseSRWLockExclusive(&Srwlock);//解除锁定，这里和关键段是有区别的
    cout << "First:" << g_nSum << endl;
    return(g_nSum);
}

int main()
{
    InitializeSRWLock(&Srwlock);
    HANDLE hThread1;

    hThread1 = CreateThread(NULL, 0, FirstThread, NULL, 0, NULL);
    WaitForSingleObject(hThread1, INFINITE);
    CloseHandle(hThread1);
    
    //如果是读取者线程的话使用：
    //VOID AcquireSRWLockShared(PSRWLOCK SRWLock);
    //VOID ReleaseSRWLockShared(PSRWLOCK SRWLock);
}
