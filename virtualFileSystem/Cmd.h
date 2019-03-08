#pragma once 
#include "MyList.h"
#include "DirObject.h"
#include "VirtualFold.h"
#include "VirtualFile.h"
#include "CmdElement.h"
#include "Msg.h"
#include <iostream>

class Cmd
{
public:
  MyList<CmdElement>* cmdElementList;
  Msg msg;

private:
  int cmdID;

public:
  virtual bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
  void SetCmdID(int cmdID);
  int GetCmdID();
};