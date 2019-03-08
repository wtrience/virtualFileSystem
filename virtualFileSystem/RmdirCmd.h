#pragma once 
#include "MyList.h"
#include "DirObject.h"
#include "Cmd.h"

class RmdirCmd : public Cmd
{
public:
  const static int PARASIZE = 10;
  MyList<DirObject> pathElesList;
  char para[PARASIZE];

private:
  int path1Type;

public:
  RmdirCmd();
  bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
  void SetPath1Type(int path1Type);
  int GetPath1Type();

private:
  void GotoRelativePreFlodPosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* delDirName, bool* flag);
  void GotoAbsolutePreFlodPosition(DirObject** curPosition, MyString* delDirName, bool* flag);
};