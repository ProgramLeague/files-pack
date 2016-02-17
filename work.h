#pragma once
#include "stdafx.h"
#include "help.h"

class pack
{
public:
  pack(TCHAR dir_out[MAX_PATH],CHAR dir_index[MAX_PATH]);//输出文件目录和XML索引目录
private:
  FILE* fpOut;
  long PackFolder(LPCTSTR szFolderPath, TiXmlElement* parent_node);
  void UnpackFolder(LPCTSTR packPath, LPCTSTR indexPath);
};
