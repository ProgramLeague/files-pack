#pragma once
#include "work.h"

/* 打包一个文件夹
* 传入文件夹完整路径及节点指针，不以斜杠结尾
* 返回值：文件夹大小
*/
long work::PackFolder(LPCTSTR szFolderPath, TiXmlElement* parent_node)
{
    char* buff;
    TCHAR2UTF8(buff, szFolderPath);
    // 父节点下新增子节点，保存文件夹名。记录节点指针
    TiXmlElement node("Folder");
    node.SetAttribute("Name", GetFolderName(buff));
    delete[] buff;
	//这里通过使用TinyXML库生成一个索引文件来帮助解包器进行文件定位
 
    // 定义变量len记录长度
    long len = 0;
 
    WIN32_FIND_DATA FindFileData;
    HANDLE hListFile;
    TCHAR szLoopPath[MAX_PATH];
    swprintf_s(szLoopPath, MAX_PATH, _T("%s\\*.*"), szFolderPath);
 
	//列出文件夹内所有文件夹
    if ((hListFile = FindFirstFile(szLoopPath, &FindFileData)) != INVALID_HANDLE_VALUE)
    {
        do
        {
            // 过滤.和..，“.”代表本级目录“..”代表父级目录
            if (lstrcmp(FindFileData.cFileName, _T(".")) == 0 ||
                lstrcmp(FindFileData.cFileName, _T("..")) == 0)
                continue;
 
            // 读取文件属性，如果是文件夹
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                TCHAR szChildFolderPath[MAX_PATH]; // 获取完整路径
                swprintf_s(szChildFolderPath, MAX_PATH, _T("%s\\%s"), szFolderPath, FindFileData.cFileName);
                // 递归，传入节点指针及文件路径，将len加上返回值 
                len += PackFolder(szChildFolderPath, &node);
            }
        }
		while (FindNextFile(hListFile, &FindFileData));
    }
    FindClose(hListFile); // 关闭句柄
 
	//列出文件夹内所有文件
    if ((hListFile = FindFirstFile(szLoopPath, &FindFileData)) != INVALID_HANDLE_VALUE)
    {
        do
        {
            // 过滤.和..，“.”代表本级目录“..”代表父级目录
            if (lstrcmp(FindFileData.cFileName, _T(".")) == 0 ||
                lstrcmp(FindFileData.cFileName, _T("..")) == 0)
                continue;
 
            // 读取文件属性，如果不是文件夹
            if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                // 获取完整文件路径
                TCHAR szFullPath[MAX_PATH];
                swprintf_s(szFullPath, MAX_PATH, _T("%s\\%s"), szFolderPath, FindFileData.cFileName);
 
                // 取文件名
                TCHAR2UTF8(buff, FindFileData.cFileName);
 
                // 打开文件并获取大小
                FILE* fpRead;
                if (_wfopen_s(&fpRead, szFullPath, _T("rb")) == 0)
                {
                    // 节点下新增子节点，设置文件名
                    TiXmlElement file_node("File");
                    file_node.SetAttribute("Name", buff);
 
                    // 获取文件大小 filelen
                    fseek(fpRead, 0, SEEK_END);
                    long filelen = ftell(fpRead);
                    fseek(fpRead, 0, SEEK_SET);
 
                    // 保存大小到节点属性
                    char szfilelen[10];
                    sprintf_s(szfilelen, "%d", filelen);
                    file_node.SetAttribute("len", szfilelen);
 
                    node.InsertEndChild(file_node);
 
                    // 将文件数据拷贝到资源包中
                    short ch;
                    while ((ch = fgetc(fpRead)) != EOF)
                    {
                        encryption(ch); // 加密
                        fputc(ch,fpOut);
                    }
 
                    // 关闭该文件
                    fclose(fpRead);
 
                    // len+=文件大小
                    len += filelen;
 
                    // 显示文件处理进度（这里要改，挪回调里去）
                    static UINT file_count = 0;
                    UINT t = ++file_count;
                    t %= 10;
                    printf("\b");
                    fflush(stdout);
                    printf("%u", t ? t : file_count);
                }
 
                delete[]buff;
            }
 
        } while (FindNextFile(hListFile, &FindFileData));
    }
    FindClose(hListFile); // 关闭句柄;
 
    // 设置节点属性 保存大小len
    char szLen[10];
    sprintf_s(szLen, 10, "%d", len);
    node.SetAttribute("len", szLen);
    parent_node->InsertEndChild(node);
 
    // 返回该文件夹的大小
    return len;
}
