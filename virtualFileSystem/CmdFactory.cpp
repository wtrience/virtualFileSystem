
#include "CmdFactory.h"
#include "CdCmd.h"
#include "CopyCmd.h"
#include "CreateNewCmd.h"
#include "DelCmd.h"
#include "DirCmd.h"
#include "ExitCmd.h"
#include "MkdirCmd.h"
#include "RmdirCmd.h"

CmdFactory::CmdFactory()
{
    
}

CmdFactory::CmdFactory(MyString command)
{
	CmdFactory();

  this->command = command;
}

Cmd* CmdFactory::CreateCmd()
{
  //分割命令元素
  cmdSplit = new CmdSplit(command);
  cmdElementList = cmdSplit->Split();

  //解析命令类型
  if(cmdElementList == NULL)
  {
    return NULL;
  }
  cmdElementList->InitList();
  cmdTypeAnalysis = new CmdTypeAnalysis();
  int cmdType = cmdTypeAnalysis->AnalysisCmdType(cmdElementList->GetCurNode());

  //创建命令,并进行初始化
  switch(cmdType)
  {
  case 1: //mkdir
    cmd = new MkdirCmd();
    break;

  case 2://cd 
    cmd = new CdCmd();
    break;

  case 3://copy
    cmd = new CopyCmd();
    break;

  case 4://del
    cmd = new DelCmd();
    break;

  case 5://rmdir
    cmd = new RmdirCmd();
    break;

  case 6://dir
    cmd = new DirCmd();
    break;


  case 9://exit
    cmd = new ExitCmd();
    break;
  default:
    std::cout << "命令不存在!" << std::endl;
  }  

  if(cmdType != -1)
  {
    cmd->SetCmdID(cmdType);

    bool pathAnalysisResult;
    pathAnalysis = new PathAnalysis(cmdElementList, cmd);
    pathAnalysisResult = pathAnalysis->Split();
    pathAnalysis->PathTypeAnalysis();
    
    if(pathAnalysisResult)
    {
      //参数解析
      cmdParaAnalysis = new CmdParaAnalysis(cmdElementList, cmd);
      cmdParaAnalysis->AnalysisPara();

      //命令格式检查
      cmdFormatCheck = new CmdFormatCheck(cmd);
      cmdFormatCheck->CheckCmdFormat();
    }
    else
    {
      cmd = NULL;
    }
  }
  else
  {
    cmd = NULL;
  }

  return cmd;
}