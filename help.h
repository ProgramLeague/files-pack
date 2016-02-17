#pragma once
#include "stdafx.h"
#include "windows.h"
#include "tinyxml.h"

/* 简单的文件保护处理（凯撒密码）
 *
 * encryption: 对每字节加一
 *
 * decryption: 对每字节减一
*/
inline void encryption(short &ch)
{
    ch = (0xFF == ch) ? 0 : ch + 1;
}
inline void decryption(short &ch)
{
    ch = (0 == ch) ? 0xFF : ch - 1;
}
 

//编码转换
inline int TCHAR2UTF8(LPSTR &lpstr, LPCTSTR lpwstr)
{
    int iSize = WideCharToMultiByte(CP_UTF8, 0, lpwstr, -1, NULL, 0, NULL, NULL);
    lpstr = new char[iSize];    // 不用+1，自动加了'\0'
    WideCharToMultiByte(CP_UTF8, 0, lpwstr, -1, lpstr, iSize, NULL, NULL);
    return iSize;
}
inline int ANSI2TCHAR(LPTSTR &lpwstr, LPCSTR lpstr)
{
    int iSize = MultiByteToWideChar(CP_ACP, 0, lpstr, -1, NULL, 0);
    lpwstr = new TCHAR[iSize];    // 不用+1，自动加了_T('\0')
    MultiByteToWideChar(CP_ACP, 0, lpstr, -1, lpwstr, iSize);
    return iSize;
}
 

//检查路径是否存在
bool isFolderExist(LPCTSTR lpPath)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hListFile = FindFirstFile(lpPath, &FindFileData);
 
    if ((hListFile != INVALID_HANDLE_VALUE) && 
        (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        return true;
    
    return false;
}
 
 
/* 通过文件夹路径获取文件夹名
 *
 * 例如 "C:\\Test\\abc"
 *
 * 窄字符和宽字符两个版本
*/
inline LPCSTR GetFolderName(LPSTR szFolderPath)
{
    UINT i = strlen(szFolderPath);
    if ('\\' == szFolderPath[i - 1])
        szFolderPath[--i] = '\0';    // 删除‘\’结尾
    do
    {
        i--;
        if (0 == i) 
			return szFolderPath;    // 无‘\’
    } 
	while ('\\' != szFolderPath[i]);
    return szFolderPath + i + 1;    // 指向文件名起点的指针
}
inline LPCTSTR GetFolderName(LPTSTR szFolderPath)
{
    UINT i = lstrlen(szFolderPath);
    if ('\\' == szFolderPath[i - 1])
        szFolderPath[--i] = '\0';    // 删除‘\’结尾
    do
    {
        i--;
        if (0 == i) 
			return szFolderPath;    // 无‘\’
    } 
	while ('\\' != szFolderPath[i]);
    return szFolderPath + i + 1;    // 指向文件名起点的指针
}
