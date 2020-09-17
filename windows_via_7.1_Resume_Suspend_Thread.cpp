// th1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "windows.h"
#include "tlhelp32.h"


using namespace std;


DWORD WINAPI testThreadProc(LPVOID lpParameter)
{
    int* p = (int*)lpParameter;//将lpParameter参数转换为int*类型的
    for (int i = 0; i < *p; i++)
    {
        
        printf("++++++++++++++++++++%d \n", i);
        Sleep(1000);
    }
    return 0;
}

VOID SuspendProcess(DWORD dwProcessID, BOOL fSuspend) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessID);

    if (hSnapshot != INVALID_HANDLE_VALUE) {
        THREADENTRY32 te = { sizeof(te) };
        BOOL f0k = Thread32First(hSnapshot, &te);
        for (; f0k; f0k = Thread32Next(hSnapshot, &te)) {
            if (te.th32OwnerProcessID == dwProcessID) {
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (hThread != NULL) {
                    if (fSuspend)
                        SuspendThread(hThread);
                    else
                        ResumeThread(hThread);
                }
                CloseHandle(hThread);
            }
        }
        CloseHandle(hSnapshot);
    }
}


int main(int argc, char* argv[])
{
    HANDLE hThread;

    int n = 10;
    hThread = CreateThread(NULL, 0, testThreadProc, &n, 0x00000004, NULL);//testThreadProc是函数名，&n是变量的地址
    for (int i = 0; i < 100; i++)
    {
        Sleep(500);
        if (i == 5) {
            ResumeThread(hThread);
        }
        if (i == 10)
        {
            SuspendProcess(GetCurrentProcessId(), true);
        }
        printf("---------%d \n", i);
    }

    CloseHandle(hThread);
    return 0;
}