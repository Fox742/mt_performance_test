#ifndef UTILS_H
#define UTILS_H



#if defined(_WIN32)
#include "windows.h"
#endif
#include <iostream>


class Utils
{
private:
#if defined(_WIN32)
    static BOOL DeleteFolderWindows(LPCWSTR szPath);
#else
    static void DeleteFolderLinux(const char *dirname);
#endif
    static bool DirExist(const std::string& path);


public:
    static bool TouchPath(const std::string& path, bool createDirectories=false);

    static void DeleteFolder(std::string path);
};

#endif // UTILS_H
