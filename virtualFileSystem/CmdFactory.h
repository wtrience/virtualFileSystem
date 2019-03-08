#pragma once 
#include "CmdFormatCheck.h"
#include "CmdParaAnalysis.h"
#include "CmdTypeAnalysis.h"
#include "PathAnalysis.h"
#include "CmdSplit.h"
#include "Cmd.h"

class CmdFactory 
{
private:
  MyString command;
  Cmd* cmd;
  MyList<CmdElement>* cmdElementList;

  PathAnalysis* pathAnalysis;
  CmdFormatCheck* cmdFormatCheck;
  CmdParaAnalysis* cmdParaAnalysis;
  CmdTypeAnalysis* cmdTypeAnalysis;
  CmdSplit* cmdSplit;

public:
  CmdFactory();
  CmdFactory(MyString command);
  Cmd* CreateCmd();
};