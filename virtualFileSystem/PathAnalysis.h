#pragma once
#include "CmdElement.h"
#include "MyList.h"
#include "DirObject.h"
#include "Cmd.h"
#include "Msg.h"

#include "CdCmd.h"
#include "CopyCmd.h"
#include "DelCmd.h"
#include "DirCmd.h"
#include "ExitCmd.h"
#include "MkdirCmd.h"
#include "RmdirCmd.h"

class PathAnalysis
{
private:
  MyList<CmdElement>* cmdElementList;
  Cmd* cmd;
  Msg msg;

  MkdirCmd* mkdir;
  CdCmd* cd;
  CopyCmd* copy;
  DelCmd* del;
  RmdirCmd* rmdir;
  DirCmd* dir;
  ExitCmd* exit;

public:
  PathAnalysis();
  PathAnalysis(MyList<CmdElement>* cmdElementList, Cmd* cmd);
  bool Split();
  void PathTypeAnalysis();
};