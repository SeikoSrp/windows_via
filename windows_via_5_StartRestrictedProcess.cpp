// windows_via_5_StartRestrictedProcess.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>

using namespace std;

void StartRestrictedProcess() {
    HANDLE hjob = CreateJobObject(NULL, NULL);//创建一个作业对象

    JOBOBJECT_BASIC_LIMIT_INFORMATION job1 = { 0 };

    job1.PriorityClass = IDLE_PRIORITY_CLASS;

    job1.PerJobUserTimeLimit.QuadPart = 10000000;

    job1.LimitFlags = JOB_OBJECT_LIMIT_PRIORITY_CLASS | JOB_OBJECT_LIMIT_JOB_TIME;

    SetInformationJobObject(hjob, JobObjectBasicLimitInformation, &job1, sizeof(job1));

    JOBOBJECT_BASIC_UI_RESTRICTIONS jobuir;
    jobuir.UIRestrictionsClass = JOB_OBJECT_UILIMIT_NONE;
    jobuir.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_EXITWINDOWS;
    jobuir.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_HANDLES;

    SetInformationJobObject(hjob, JobObjectBasicUIRestrictions, &jobuir, sizeof(jobuir));

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    TCHAR szCommandLine[] = TEXT("calc");
    //创建进程
    CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);

    AssignProcessToJobObject(hjob, pi.hProcess);//将进程分配给现有的作业对象

    ResumeThread(pi.hThread);
    CloseHandle(pi.hThread);

    HANDLE h[2];
    h[0] = pi.hProcess;
    h[1] = hjob;
    DWORD dw = WaitForMultipleObjects(2, h, FALSE, INFINITE);
    switch (dw - WAIT_OBJECT_0) {
    case 0:
        cout << "0";
        break;
    case 1:
        cout << "1";
        break;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(hjob);
}

int main()
{
    std::cout << "Hello World!\n";
    StartRestrictedProcess();
}
