#pragma once
#include "stdafx.h"
#include "windows.h"
#include "tinyxml.h"
#include "help.h"

class pack
{
public:
  pack(); //tik
  FILE* fpOut;
  long PackFolder(LPCTSTR szFolderPath, TiXmlElement* parent_node);
  void UnpackFolder(LPCTSTR packPath, LPCTSTR indexPath);
};
