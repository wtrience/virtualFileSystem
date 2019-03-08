#pragma once 
#include "MyList.h"
#include "DirObject.h"
#include "Cmd.h"

class DirCmd : public Cmd
{
public:
  const static int PARASIZE = 10;
  MyList<DirObject> pathElesList;
  char para[PARASIZE];

private:
  int path1Type;
  
public:
  DirCmd();
  bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
  void SetPath1Type(int path1Type);
  int GetPath1Type();

private:
  void DirCmd::GotoRelativeSearchPosition(DirObject** curPosition, MyList<DirObject>* workingPath, bool* flag);
  void DirCmd::GotoAbsoluteSearchPosition(DirObject** curPosition, bool* flag);

  void DisplayChildrenNode(DirObject* curPosition, bool flag);
  void DisplayChildrenFold(DirObject* curPosition, bool flag);
  void DisplayAll(DirObject* curPosition, bool flag);
};  