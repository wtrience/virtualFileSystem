
#include "CmdFormatCheck.h"

CmdFormatCheck::CmdFormatCheck()
{

}

CmdFormatCheck::CmdFormatCheck(Cmd* cmd)
{
  CmdFormatCheck();

  this->cmd = cmd;
}

bool CmdFormatCheck::CheckCmdFormat()
{
  return false;
}