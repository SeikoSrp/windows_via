// windows_via_17.7_MapViewOfFile_Details.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <strsafe.h>

using namespace std;

int main()
{
	HANDLE hFile = CreateFile(
		TEXT("test.exe"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);


	HANDLE hFileMapping = CreateFileMapping(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		0,
		NULL);

	PBYTE pbFile = (PBYTE)MapViewOfFile(
		hFileMapping, FILE_MAP_WRITE, 0, 0, 0
	);

	PBYTE pbFile2 = (PBYTE)MapViewOfFile(
		hFileMapping, FILE_MAP_WRITE, 0, 65536, 0
	);


	int iDifference = int(pbFile2 - pbFile);
	cout << iDifference << endl;
	TCHAR szMsg[100];
	StringCchPrintf(szMsg, _countof(szMsg),
		TEXT("Pointers difference = %d KB"), iDifference / 1024);
	MessageBox(NULL, szMsg, NULL, MB_OK);

	UnmapViewOfFile(pbFile2);
	UnmapViewOfFile(pbFile);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);


	return 0;
}

