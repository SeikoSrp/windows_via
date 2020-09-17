// windows_via_3.3.6_DuplicateHandle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>

using namespace std;

int main()
{
    //创建一个互斥内核对象
    HANDLE hObjInProcessS = CreateMutex(NULL, FALSE, NULL);


    //根据PID获取一个进程的句柄
    HANDLE hProcessT = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());

    //定义一个未初始化的句柄
    HANDLE hObjInProcessT;

    //DuplicateHandle获取第二个参数的伪句柄并将真实句柄返回给hObjInProcessT（参数四）
    DuplicateHandle(GetCurrentProcess(), hObjInProcessS, hProcessT, &hObjInProcessT, 0, FALSE, DUPLICATE_SAME_ACCESS);

    cout << "[+]real handle "<< hObjInProcessT <<endl;
    
    CloseHandle(hProcessT);

    CloseHandle(hObjInProcessS);


}
