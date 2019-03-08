#pragma once 
#include "MyString.h"
#include "MyList.h"
#include "CmdElement.h"
#include "Msg.h"

class CmdSplit
{
private:
  MyString cmd;
  MyList<CmdElement> cmdElementsList;
  int cmdID;
  Msg msg;

public:
  CmdSplit();
  CmdSplit(MyString cmd);
  MyList<CmdElement>* Split();

  void SetCmd(MyString cmd);
};