#include "pack.h"

int _tmain(int argc, _TCHAR* argv[]) //命令行传参调用
{
    TCHAR dir_in[MAX_PATH];           // 打包目录
    TCHAR dir_out[MAX_PATH];          // 输出目录
    TCHAR dir_index[MAX_PATH];        // 索引文件目录
 
    switch (argc)
    {
    case 2:
        // 检查路径是否合法（不允许反斜线结束）
        if (isFolderExist(argv[1]))
        {
            lstrcpynW(dir_in, argv[1], MAX_PATH);
            swprintf_s(dir_out, MAX_PATH, _T("%s.pak"), dir_in);
            swprintf_s(dir_index, MAX_PATH, _T("%s.dat"), dir_in);
        }
        else
        {
            printf_s("无法打开指定的路径\n");
            return 0;
        }
        break;
        
    case 3:
        if (isFolderExist(argv[1]) && isFolderExist(argv[2]))
        {
            lstrcpynW(dir_in, argv[1], MAX_PATH);
            swprintf_s(dir_out, MAX_PATH, _T("%s\\%s.pak"), argv[2], GetFolderName(argv[2]));
            swprintf_s(dir_index, MAX_PATH, _T("%s\\%s.dat"), argv[2], GetFolderName(argv[2]));
        }
        else
        {
            printf_s("无法打开指定的路径\n");
            return 0;
        }
        break;
        
    default:
        printf_s("用法： KEPacker 资源目录 [输出目录]\n注意： 路径不能以反斜线结尾\n");
        return 0;
    }
 
    try
    {
        pack mypack(dir_out, TCHAR dir_index, TCHAR dir_in);
    }
    catch(int)
    {
        printf_s("打包过程中出现错误\n");
    }
    
    getchar();
    return 0;
}
