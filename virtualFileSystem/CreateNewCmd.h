#pragma once 
#include "MyList.h"
#include "DirObject.h"
#include "Cmd.h"

class CreateNewCmd : public Cmd
{
public:
  MyList<DirObject> pathElesList;

private:
  int path1Type;

public:
  bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
  void SetPath1Type(int path1Type);
  int GetPath1Type();

private:
  //包含该文件的文件夹查找
  void GotoAbsolutePreFlodPosition(DirObject** curPosition, MyString* createDirName, bool* flag);
  void GotoRelativePreFlodPosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* createDirName, bool* flag);
};