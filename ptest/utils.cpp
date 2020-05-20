#include "utils.h"
#include <sys/types.h> // stat
#include <sys/stat.h> // stat
#include <string.h>

#if defined(_WIN32)
#include <direct.h>   // _mkdir
#include <windows.h>
#include <fileapi.h>
#include <tchar.h>
#include <stdio.h>

#include <fileapi.h>

using namespace std;
#else
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#endif


bool Utils::DirExist(const std::string& path)
{
#if defined(_WIN32)
    struct _stat info;
    if (_stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & _S_IFDIR) != 0;
#else
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
#endif
}

bool Utils::TouchPath(const std::string& path, bool createDirectories)
{
    if (DirExist(path))
    {
        return true;
    }
    else
    {
        if (!createDirectories)
            return false;
    }

#if defined(_WIN32)
    int ret = _mkdir(path.c_str());
#else
    mode_t mode = 0755;
    int ret = mkdir(path.c_str(), mode);
#endif
    if (ret == 0)
        return true;

    switch (errno)
    {
    case ENOENT:
        // parent didn't exist, try to create it
        {
            int pos = path.find_last_of('/');
            if (pos == std::string::npos)
#if defined(_WIN32)
                pos = path.find_last_of('\\');
            if (pos == std::string::npos)
#endif
                return false;
            if (!TouchPath( path.substr(0, pos),createDirectories ))
                return false;
        }
        // now, try to create again
#if defined(_WIN32)
        return 0 == _mkdir(path.c_str());
#else
        return 0 == mkdir(path.c_str(), mode);
#endif

    case EEXIST:
        // done!
        return DirExist(path);

    default:
        return false;
    }
}

bool Utils::isDirectory(std::string path)
{
#if defined(_WIN32)
    wstring wpath = wstring(path.begin(), path.end());
    if (GetFileAttributes(wpath.c_str()) & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;
    }
    return false;
#else
    struct stat s;
    if( lstat(path.c_str(),&s) == 0 )
    {
        if (S_ISLNK(s.st_mode))
        {
            return false;
        }
        if( s.st_mode & S_IFDIR )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
#endif
}

#if defined(_WIN32)
//Рекурсивное удаление каталога
BOOL Utils::DeleteFolderWindows(LPCWSTR szPath)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError,dwAttrs;
    BOOL bRes;
    int nLength;
    wchar_t cPath[MAX_PATH],cCurrentFile[MAX_PATH];

    if (szPath == NULL)
        return FALSE;

    if (lstrcmpi(szPath + 1, TEXT(":")) == 0 || szPath[0] == '\\' || szPath[0] == '\0')
        return FALSE;

//Объекта уже нет
    dwAttrs = GetFileAttributes(szPath);
    if (dwAttrs == INVALID_FILE_ATTRIBUTES)
        return TRUE;

//Если объект не директория
    if (~dwAttrs & FILE_ATTRIBUTE_DIRECTORY)
            DeleteFile (szPath);

    SetLastError(0);

//Пробуем сразу удалить директорию
    bRes = RemoveDirectory(szPath);
    if (bRes == TRUE)
        return TRUE;

    if (bRes == FALSE  && GetLastError() != ERROR_DIR_NOT_EMPTY)
        return FALSE;

    nLength = lstrlen(szPath);

    if (nLength + lstrlen(L"\\*.*") + 1> MAX_PATH)
        return FALSE;

    if (szPath[nLength - 1] == '\\')
        wsprintf(cPath,L"%s*.*",szPath);
    else
        wsprintf(cPath,L"%s\\*.*",szPath);

    hFind = FindFirstFile(cPath, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
        return FALSE;

    lstrcpy(cPath,szPath);

    if (cPath[nLength - 1] == '\\')
        cPath[nLength - 1] = TEXT('\0');

    do
    {
//Опускаем начальные . и ..
        if (lstrcmpi(FindFileData.cFileName, L".") == 0 || lstrcmpi(FindFileData.cFileName, L"..") == 0)
            continue;

//Пропускаем слишком длинные имена файлов
        if (lstrlen(cPath) + lstrlen(L"") +  lstrlen(FindFileData.cFileName) + 1 > MAX_PATH)
            continue;

        wsprintf(cCurrentFile,L"%s\\%s",cPath,FindFileData.cFileName);
//Удаляем папку
        if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
//Сбрасываем аттрибуты
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
            {
                FindFileData.dwFileAttributes &= ~FILE_ATTRIBUTE_READONLY;
                SetFileAttributes(cCurrentFile,FindFileData.dwFileAttributes);
            }

            bRes = DeleteFolderWindows(cCurrentFile);
        }
//Иначе удаляем файл
        else
        {

            if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ||
                (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
                SetFileAttributes (cCurrentFile, FILE_ATTRIBUTE_NORMAL);

            DeleteFile (cCurrentFile);
        }
    }
    while (FindNextFile(hFind,&FindFileData));

    dwError = GetLastError();

    if (hFind != INVALID_HANDLE_VALUE)
        FindClose(hFind);

    if (dwError != ERROR_NO_MORE_FILES)
        return FALSE;

    bRes = RemoveDirectory(szPath);

    return bRes;
}
#endif

#ifndef _WIN32
void Utils::DeleteFolderLinux(const char *dirname)
{
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];

    if (path == NULL)
    {
        return;
    }

    if (!isDirectory(dirname))
    {
        unlink(dirname);
    }

    dir = opendir(dirname);
    if (dir == NULL)
    {
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
        {
            snprintf(path, (size_t) PATH_MAX, "%s/%s", dirname, entry->d_name);
            if (entry->d_type == DT_DIR)
            {
                DeleteFolderLinux(path);
                rmdir(path);
            }
            else
            {
                // Удаляем файл
                unlink(path);
            }
        }

    }
    closedir(dir);
    rmdir(dirname);
}
#endif

void Utils::DeleteFolder(std::string path)
{
#if defined (_WIN32)
    std::wstring stemp = std::wstring(path.begin(),path.end());
    LPCWSTR pathW = stemp.c_str();
    Utils::DeleteFolderWindows(pathW);
#else
    Utils::DeleteFolderLinux(path.c_str());
#endif
}
