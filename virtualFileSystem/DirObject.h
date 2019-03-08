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
  int typeFlag;         //typeFlag==0�����ļ���,typeFlag==1�����ļ�,typeFlag==2�����̷�


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