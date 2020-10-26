#include <windows.h>
#include <iostream>
#include <synchapi.h>

using namespace std;

HANDLE g_hEvent;

DWORD WINAPI ThreadProc_1(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };
	//等待事件g_hEvent
	WaitForSingleObject(g_hEvent, INFINITE);

	for (int i = 0; i < 10; i++) {
		cout << "ThreadProc_1 exec " << endl;
		Sleep(500);
	}
	//系统自动重置之后需要使用SetEvent设置为触发状态，其他线程才能继续执行
	SetEvent(g_hEvent);
	return 0;
}

DWORD WINAPI ThreadProc_2(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };

	WaitForSingleObject(g_hEvent, INFINITE);

	for (int i = 0; i < 10; i++) {
		cout << "ThreadProc_2 exec " << endl;
		Sleep(500);
	}

	SetEvent(g_hEvent);
	return 0;
}

int main(int argc, char* argv[])
{

	//第二个参数设置为FALSE，也就是自动重置，也就是一个线程等待到了事件触发状态之后会把事件触发状态重置为未触发状态，其他线程就等不到这个事件对象的触发状态了
	//第三个参数设置为False，也就是事件的初始状态为未触发
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hThread[2];
	//创建2个线程
	hThread[0] = CreateThread(NULL, 0, ThreadProc_1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ThreadProc_2, NULL, 0, NULL);

	//上面CreateEvent第三个参数设置事件为未触发状态，需要设置成触发状态线程才能wait到
	SetEvent(g_hEvent);

	//等待线程结束，销毁内核对象
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(g_hEvent);

	return 0;
}