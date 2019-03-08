
#include "Cmd.h"

bool Cmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  return false;
}

void Cmd::SetCmdID(int cmdID)
{
  this->cmdID = cmdID;
}

int Cmd::GetCmdID()
{
  return cmdID;
}