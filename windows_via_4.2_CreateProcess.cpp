#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void _tmain(int argc, TCHAR* argv[])
{
    //STARTUPINFO si;
    //PROCESS_INFORMATION pi;
    ////ZeroMemory使用0填充内存块，&si为起始指针,sizeof(si)为长度
    //ZeroMemory(&si, sizeof(si));
    //si.cb = sizeof(si);
    //ZeroMemory(&pi, sizeof(pi));

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    TCHAR szCommandLine[] = TEXT("WORDPAD NOTEPAD.TXT");

    // Start the child process. 
    if (!CreateProcess(TEXT("C:\\Windows\\System32\\NOTEPAD.EXE"), szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}