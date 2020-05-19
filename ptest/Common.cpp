#include "common.h"
#include <vector>
#include "iostream"
#include "sstream"

void ClearScreen()
{
#if defined(_WIN32)
    std::system("cls");
#else
    std::system ("clear");
#endif
}
