
#include "CmdSplit.h"
#include <iostream>

CmdSplit::CmdSplit()
{

}

CmdSplit::CmdSplit(MyString cmd)
{
  this->cmd = cmd;
}

MyList<CmdElement>* CmdSplit::Split()
{
  int source_index = 0;
  int destination_index = 0;

  //���ȷ��������������ַ�����ʼ����һ���ո�֮ǰ
  CmdElement* cmdName = new CmdElement();
  while(cmd.data[source_index] != ' ' && cmd.data[source_index] != '\0')
  {
    cmdName->data[destination_index++] = cmd.data[source_index++];
  }
  cmdName->SetElementsType(msg.CMD_NAME);
  cmdElementsList.AddNode(*cmdName);
  source_index++;   //�����ո�
  destination_index = 0;

  //'/'�ǲ������������Ǻ�˫���ŵ�·���ַ���������Ϊ��ͨ·���ַ���
  char temp = cmd.data[source_index];
  while(temp == '/' && cmd.data[source_index+1] != '\0')
  {
    CmdElement* cmdPara = new CmdElement();
    while(cmd.data[source_index] != ' ' && cmd.data[source_index] != '\0')
    {
      cmdPara->data[destination_index++] = cmd.data[source_index++];
    }
    cmdPara->SetElementsType(msg.CMD_PARA);
    cmdElementsList.AddNode(*cmdPara);
    source_index++; //�����ո�
    destination_index = 0;

    temp = cmd.data[source_index];
  }

  //Ȼ������Ƿ���·��1
  while(cmd.data[source_index] != '\0')
  {
    while(temp == '\"')
    {
      CmdElement* cmdPath = new CmdElement();
      source_index++;
      while(cmd.data[source_index] != '\"')
      {
        if(cmd.data[source_index] == '\0')
        {
          //���Ų�ƥ��
          std::cout << msg.QUOTATION_DONOT_MATCH << std::endl;
          return NULL;
        }
        cmdPath->data[destination_index++] = cmd.data[source_index++];
      }
      cmdPath->SetElementsType(msg.CMD_PATH);
      cmdElementsList.AddNode(*cmdPath);
      source_index+=2;  //�������źͿո�
      destination_index = 0;

      temp = cmd.data[source_index];
    }

    while(temp != '\0')
    {
      CmdElement* cmdPath = new CmdElement();
      while(cmd.data[source_index] != ' ' && cmd.data[source_index] != '\0')
      {
        cmdPath->data[destination_index++] = cmd.data[source_index++];
      }
      cmdPath->SetElementsType(msg.CMD_PATH);
      cmdElementsList.AddNode(*cmdPath);
      if(cmd.data[source_index] == ' ')
      {
        source_index++; //�����ո�
      }
      destination_index = 0;

      temp = cmd.data[source_index];
    }
  }
  
  return &cmdElementsList;
}

void CmdSplit::SetCmd(MyString cmd)
{
  this->cmd = cmd;
}