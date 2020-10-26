#include <windows.h>
#include <stdio.h>
#include <tchar.h>

// Use to convert bytes to KB
#define DIV 1024

// Specify the width of the field in which to print the numbers. 
// The asterisk in the format specifier "%*I64d" takes an integer 
// argument and uses it to pad and right justify the number.
#define WIDTH 7

void _tmain()
{
    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof(statex);//在将地址带入到GlobalMemoryStatusEx函数之前，MEMORYSTATUSEX结构的dwLength必须要初始化

    GlobalMemoryStatusEx(&statex);

    _tprintf(TEXT("There is  %*ld percent of memory in use.\n"),
        WIDTH, statex.dwMemoryLoad);
    _tprintf(TEXT("There are %*I64d total KB of physical memory.\n"),
        WIDTH, statex.ullTotalPhys / DIV);
    _tprintf(TEXT("There are %*I64d free  KB of physical memory.\n"),
        WIDTH, statex.ullAvailPhys / DIV);
    _tprintf(TEXT("There are %*I64d total KB of paging file.\n"),
        WIDTH, statex.ullTotalPageFile / DIV);
    _tprintf(TEXT("There are %*I64d free  KB of paging file.\n"),
        WIDTH, statex.ullAvailPageFile / DIV);
    _tprintf(TEXT("There are %*I64d total KB of virtual memory.\n"),
        WIDTH, statex.ullTotalVirtual / DIV);
    _tprintf(TEXT("There are %*I64d free  KB of virtual memory.\n"),
        WIDTH, statex.ullAvailVirtual / DIV);

    // Show the amount of extended memory available.

    _tprintf(TEXT("There are %*I64d free  KB of extended memory.\n"),
        WIDTH, statex.ullAvailExtendedVirtual / DIV);
}