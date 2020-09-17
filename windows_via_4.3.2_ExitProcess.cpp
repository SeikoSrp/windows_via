// windows_via_4.3.2_ExitProcess.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <stdio.h>

class CSomeObj {
public:
    CSomeObj() { printf("Constructor \r\n"); }
    ~CSomeObj() { printf("Destructor \r\n"); }
};

CSomeObj g_GlobalObj;

void main()
{
    std::cout << "Hello World!\n";
    CSomeObj LocalObj;
    ExitProcess(0);
}

