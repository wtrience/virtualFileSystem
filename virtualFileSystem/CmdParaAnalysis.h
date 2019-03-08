#pragma once

#include "DirCmd.h"
#include "RmdirCmd.h"
#include "Cmd.h"
#include "MyList.h"
#include "Msg.h"

class CmdParaAnalysis
{
private:
  MyList<CmdElement>* cmdElementList;
  Cmd* cmd;
  Msg msg;

  RmdirCmd* rmdir;
  DirCmd* dir;

public:
  CmdParaAnalysis();
  CmdParaAnalysis(MyList<CmdElement>* cmdElementList, Cmd* cmd);
  void AnalysisPara();
};