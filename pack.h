#pragma once
#include "stdafx.h"
#include "help.h"

class pack
{
public:
  pack(TCHAR dir_out[], TCHAR dir_index[], TCHAR dir_in[])
    :dir_out(dir_out),dir_index(dir_index),dir_in(dir_in){} //输出文件目录、XML索引目录、输入文件目录（注意，要打包和要解包输出输入可是不一样的）
  void setIO(TCHAR dir_out[], TCHAR dir_in[]){
    this->dir_out=dir_out;
    this->dir_in=dir_in;
  }
  void GoPack();
  void GoUnpack();
  
private:
  FILE* fpOut;
  void PackFolder(LPCTSTR szFolderPath, TiXmlElement* parent_node);
  void UnpackFolder(LPCTSTR packPath, LPCTSTR indexPath);
  
  //注意不要出翔（VC太蛋疼
  TCHAR dir_out[];
  TCHAR dir_index[];
  TCHAR dir_in[];
};
