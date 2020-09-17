#include <iostream>
#include "windows.h"
#include "timezoneapi.h"

using namespace std;

int main(int argc, char* argv[])
{

    FILETIME c, e, k, u;
    GetThreadTimes(GetCurrentThread(), &c, &e, &k, &u);
    SYSTEMTIME sc;
    FileTimeToSystemTime(&c,&sc);
    cout << sc.wYear<< " " <<sc.wMonth << " " <<sc.wDay << " " <<sc.wHour << " " <<sc.wMinute<< endl;

    return 0;
}