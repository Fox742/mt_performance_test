#include "Common.h"
#include <vector>
#include "iostream"
#include "sstream"

#if defined(_WIN32)
#include "windows.h"
#else
#include <unistd.h>
#endif

void ClearScreen()
{
#if defined(_WIN32)
    std::system("cls");
#else
    std::system ("clear");
#endif
}

void PTestSleep(unsigned int msToSleep)
{
#if defined(_WIN32)
    Sleep(msToSleep);
#else
    usleep(msToSleep);
#endif
}
