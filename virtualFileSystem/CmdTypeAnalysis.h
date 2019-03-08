#pragma once
#include "CmdElement.h"
#include "Msg.h"

class CmdTypeAnalysis
{
private:
  Msg msg;
  int cmdType;

public:
  CmdTypeAnalysis();
  int AnalysisCmdType(CmdElement* cmdName);
};