
#include "CmdParaAnalysis.h"

CmdParaAnalysis::CmdParaAnalysis()
{

}

CmdParaAnalysis::CmdParaAnalysis(MyList<CmdElement>* cmdElementList, Cmd* cmd)
{
  CmdParaAnalysis();

  this->cmdElementList = cmdElementList;
  this->cmd = cmd;
}

void CmdParaAnalysis::AnalysisPara()
{
  int cmdType = cmd->GetCmdID();
  int index = 0;
  int sourceIndex = 0;

  CmdElement* cmdElementNode;
  switch(cmdType)
  {
  case msg.RMDIRCMD:
    rmdir = (RmdirCmd*)cmd;
    cmdElementList->InitList();
    while(cmdElementList->GetNextNode() != NULL)
    {
      cmdElementNode = cmdElementList->GetCurNode();
      if(cmdElementNode->GetElementsType() == msg.CMD_PARA)
      {
        sourceIndex = 0;
        while(cmdElementNode->data[sourceIndex] != '\0')
          rmdir->para[index++] = cmdElementNode->data[sourceIndex++];
      }
    }
    break;
  case msg.DIRCMD:
    dir = (DirCmd*)cmd;
    cmdElementList->InitList();
    while(cmdElementList->GetNextNode() != NULL)
    {
      cmdElementNode = cmdElementList->GetCurNode();
      if(cmdElementNode->GetElementsType() == msg.CMD_PARA)
      {
        sourceIndex = 0;
        while(cmdElementNode->data[sourceIndex] != '\0')
          dir->para[index++] = cmdElementNode->data[sourceIndex++];
      }
    }
    break;
  }
}