// windows_via_14.4_VirtualQuery.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <Windows.h>

using namespace std;

BOOL iteratorMemory(DWORD dwPid)
{
	//判断进程是否为0和4，也就是空闲进程和System进程
	if (dwPid == 0 || dwPid == 4)
		return FALSE;

	HANDLE hProcess = 0;
	DWORD dwTempSize = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	if (!hProcess)
	{
		cout << "OpenProcess Failed~" << endl;
		return FALSE;
	}

	PMEMORY_BASIC_INFORMATION pMemInfo = new MEMORY_BASIC_INFORMATION();
	DWORD dwErrorCode;
	dwErrorCode = VirtualQueryEx(hProcess, 0, pMemInfo, sizeof(MEMORY_BASIC_INFORMATION));
	if (0 == dwErrorCode)
	{
		cout << "dwErrorCode = 0" << endl;
		return FALSE;
	}

	for (__int64 i = pMemInfo->RegionSize; i < (i + pMemInfo->RegionSize); i += pMemInfo->RegionSize)
	{
		dwErrorCode = VirtualQueryEx(hProcess, (LPVOID)i, pMemInfo, sizeof(MEMORY_BASIC_INFORMATION));
		if (dwErrorCode == 0)
			break;
		cout << pMemInfo->BaseAddress << "   ";
		cout << pMemInfo->AllocationBase << "  " << pMemInfo->RegionSize << "  ";
		switch (pMemInfo->AllocationProtect)
		{
		case 16:printf(" PAGE_EXECUTE "); break;
		case 32:printf(" PAGE_EXECUTE_READ "); break;
		case 64:printf(" PAGE_EXECUTE_READWRITE "); break;
		case 128:printf(" PAGE_EXECUTE_WRITECOPY "); break;
		case 1:printf(" PAGE_NOACCESS "); break;
		case 2:printf(" PAGE_READONLY "); break;
		case 4:printf(" PAGE_READWRITE "); break;
		case 8:printf(" PAGE_WRITECOPY "); break;
		case 1073741824:printf(" PAGE_TARGETS_INVALID "); break;
		case 256:printf(" PAGE_GUARD "); break;
		case 512:printf(" PAGE_NOCACHE "); break;
		case 1024:printf(" PAGE_WRITECOMBINE "); break;
		default:printf(" unkown AllocationProtect"); break;
		}
		switch (pMemInfo->State)
		{
		case 4096:printf(" MEM_COMMIT "); break;
		case 65536:printf(" MEM_FREE "); break;
		case 8192:printf(" MEM_RESERVE "); break;
		default:printf(" unkown State");
		}
		cout << "  ";
		switch (pMemInfo->Protect)
		{
		case 16:printf(" PAGE_EXECUTE "); break;
		case 32:printf(" PAGE_EXECUTE_READ "); break;
		case 64:printf(" PAGE_EXECUTE_READWRITE "); break;
		case 128:printf(" PAGE_EXECUTE_WRITECOPY "); break;
		case 1:printf(" PAGE_NOACCESS "); break;
		case 2:printf(" PAGE_READONLY "); break;
		case 4:printf(" PAGE_READWRITE "); break;
		case 8:printf(" PAGE_WRITECOPY "); break;
		case 1073741824:printf(" PAGE_TARGETS_INVALID "); break;
		case 256:printf(" PAGE_GUARD "); break;
		case 512:printf(" PAGE_NOCACHE "); break;
		case 1024:printf(" PAGE_WRITECOMBINE "); break;
		default:printf(" unkown "); break;
		}
		cout << "  ";
		switch (pMemInfo->Type)
		{
		case 16777216:printf(" MEM_IMAGE ");
		case 16384:printf(" MEM_MAPPED ");
		case 8192:printf(" MEM_PRIVATE ");
		default:printf(" unkown Type\n\n");
		}
	}
	return FALSE;
}


int main()
{
	std::cout << "Hello World!\n";
	DWORD pid = 2544;
	iteratorMemory(pid);
}
