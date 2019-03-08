#pragma once 
#include "CmdElement.h"
#include "CdCmd.h"
#include "CopyCmd.h"
#include "DelCmd.h"
#include "DirCmd.h"
#include "ExitCmd.h"
#include "MkdirCmd.h"
#include "RmdirCmd.h"
#include "Cmd.h"
#include "Msg.h"

class CmdFormatCheck
{
private:
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
  CmdFormatCheck();
  CmdFormatCheck(Cmd* cmd);
  bool CheckCmdFormat();
};