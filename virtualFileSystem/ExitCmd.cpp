
#include "ExitCmd.h"

bool ExitCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  exit(0);
  return false;
}