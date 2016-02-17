#pragma once
#include "stdafx.h"
#include "help.h"

class pack
{
public:
  pack(TCHAR dir_out[MAX_PATH], TCHAR dir_index[MAX_PATH], TCHAR dir_in[MAX_PATH]);//输出文件目录、XML索引目录、被打包文件目录
private:
  FILE* fpOut;
  long PackFolder(LPCTSTR szFolderPath, TiXmlElement* parent_node);
  void UnpackFolder(LPCTSTR packPath, LPCTSTR indexPath);
};
