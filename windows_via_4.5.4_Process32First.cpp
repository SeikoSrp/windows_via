// windows_via_4.5.4_Process32First.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

using namespace std;

int main()
{
    HANDLE hProcess;

    PROCESSENTRY32 mype;
    mype.dwSize = sizeof(PROCESSENTRY32);//这里如果执行了Process32First返回false，并且GetLastError返回24要把这一句加上
    //官方文档里写的有https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32
    BOOL mybRet;

    hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    mybRet = Process32First(hProcess, &mype);

    while (Process32Next(hProcess, &mype))
    {
        wcout << mype.szExeFile <<"   ------   " << mype.th32ProcessID<< endl;
        //szExeFile为宽字节类型，所以需要使用wcout，不然会输出为16进制的字符
    }
}
