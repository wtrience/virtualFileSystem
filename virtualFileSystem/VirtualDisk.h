#pragma once
#include <iostream>
#include "MyString.h"
#include "MyList.h"
#include "DirObject.h"
#include "CmdFactory.h"

class VirtualDisk
{
public:
  VirtualDisk();
  void InitFileSys();
  void CmdExecute(MyString cmd);

  MyString GetWorkingPath();
  void SetWorkingPath(MyList<DirObject>* workingPath);

private:
  MyString cmd_str;
  Cmd* cmd_object;
  DirObject* rootDir;
  MyList<DirObject> workingPath;
  CmdFactory* cmdFactory;
};