
#include "CmdTypeAnalysis.h"
#include "stdlib.h"
#include <iostream>

CmdTypeAnalysis::CmdTypeAnalysis()
{
  cmdType = -1;
}

int CmdTypeAnalysis::AnalysisCmdType(CmdElement *cmdName)
{
  MyString* cmdName_str = (MyString*)cmdName;
  int flag = -1;

  //mkdir
  flag = strcmp(cmdName_str->data, msg.MKDIR);
  if(flag == 0)
    cmdType = msg.MKDIRCMD;

  //cd
  flag = strcmp(cmdName_str->data, msg.CD);
  if(flag == 0)
    cmdType = msg.CDCMD;
  
  //copy
  flag = strcmp(cmdName_str->data, msg.COPY);
  if(flag == 0)
    cmdType = msg.COPYCMD;

  //del
  flag = strcmp(cmdName_str->data, msg.DEL);
  if(flag == 0)
    cmdType = msg.DELCMD;

  //rmdir
  flag = strcmp(cmdName_str->data, msg.RMDIR);
  if(flag == 0)
    cmdType = msg.RMDIRCMD;

  //dir
  flag = strcmp(cmdName_str->data, msg.DIR);
  if(flag == 0)
    cmdType = msg.DIRCMD;

  //compare
  flag = strcmp(cmdName_str->data, msg.COMPARE);
  if(flag == 0)
    cmdType = msg.COMPARECMD;


  //exit
  flag = strcmp(cmdName_str->data, msg.EXIT);
  if(flag == 0)
    cmdType = msg.EXITCMD;

  return cmdType;
}