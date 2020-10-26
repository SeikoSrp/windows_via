// windows_via_8.2_GetLogicalProcessorInformation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <sysinfoapi.h>

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION XBuffer = NULL;
    DWORD ReturnLength = NULL;
    if (GetLogicalProcessorInformation(XBuffer, &ReturnLength)) {
        cout << XBuffer->Cache.LineSize << endl;
    }
    else {
        cout << "false" << endl;
        cout << GetLastError() << endl;
    }

}
