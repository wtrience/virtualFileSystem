#pragma once 
#include "MyList.h"
#include "DirObject.h"
#include "Cmd.h"

class CdCmd : public Cmd
{
public:
  MyList<DirObject> pathElesList;

private:
  int path1Type;

public:
  bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
  void SetPath1Type(int path1Type);
  int GetPath1Type();
};