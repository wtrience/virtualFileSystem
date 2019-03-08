#pragma once 
#include "MyString.h"
#include "MyList.h"
#include "DirObject.h"

class DirObject
{
public:
  MyList<DirObject> childrenLink;
  const static int SIZE = 10000;
  char content[SIZE];

protected:
  MyString dirName;
  int typeFlag;         //typeFlag==0代表文件夹,typeFlag==1代表文件,typeFlag==2代表盘符


public:
  DirObject();
  DirObject(MyString dirName);
  virtual DirObject operator = (DirObject value);
  virtual bool operator == (DirObject value);
  DirObject* Find(MyString name);
  int TypeAnalysis();
  bool AddDirNode(DirObject* node);

  MyString GetDirName();
  void SetDirName(MyString name);

  int GetTypeFlag();
  void SetTypeFlag(int typeFlag);
};