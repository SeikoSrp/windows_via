#include <iostream>
#include <windows.h>
#include <shellapi.h>

int main()
{
    //首先构造一个SHELLEXECUTEINFO结构
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = TEXT("runas");//加了runas会使用管理员权限
    ShExecInfo.lpFile = TEXT("C:\\Windows\\System32\\cmd.exe");//要执行的文件
    ShExecInfo.lpParameters = TEXT("");
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;

    //执行ShellExecuteEx
    ShellExecuteEx(&ShExecInfo);

    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
}