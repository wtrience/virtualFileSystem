
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
  //�ָ�����Ԫ��
  cmdSplit = new CmdSplit(command);
  cmdElementList = cmdSplit->Split();

  //������������
  if(cmdElementList == NULL)
  {
    return NULL;
  }
  cmdElementList->InitList();
  cmdTypeAnalysis = new CmdTypeAnalysis();
  int cmdType = cmdTypeAnalysis->AnalysisCmdType(cmdElementList->GetCurNode());

  //��������,�����г�ʼ��
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
    std::cout << "�������!" << std::endl;
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
      //��������
      cmdParaAnalysis = new CmdParaAnalysis(cmdElementList, cmd);
      cmdParaAnalysis->AnalysisPara();

      //�����ʽ���
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