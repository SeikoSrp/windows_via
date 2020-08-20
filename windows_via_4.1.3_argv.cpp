#include <iostream>
#include <windows.h>

using namespace std;

void main(int argc, char* argv[])
{
	int nNumArgs;
	int i;
	PWSTR* ppArgv = CommandLineToArgvW(GetCommandLineW(), &nNumArgs);
	cout << nNumArgs << endl;
	if (ppArgv == NULL) {
		cout << " failed ~" << endl;
	}
	else {
		for (i = 0; i < nNumArgs; i++) {
			printf("%ws\n", ppArgv[i]);
		}
	}
}