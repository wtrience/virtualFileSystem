#pragma once 
#include "MyList.h"
#include "Cmd.h"

class ExitCmd : public Cmd
{
public:
  bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
};