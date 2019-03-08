
#include "DirCmd.h"

DirCmd::DirCmd()
{
  for(int i=0; i<PARASIZE; i++)
    para[i] = '\0';
}

bool DirCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;                   //��¼�����Ƿ�ִ�гɹ�
  DirObject* curPosition = rootDir;   //��¼��ǰλ��
  DirObject* dirNode = NULL;          //��ʱ����DirObject����

  //������������
  int paraType = -1;
  if(para[0] == '\0')//����Ϊ��ʱ��paraTypeΪ0
    paraType = 0;     

  for(int i=0; para[i] != '\0'; i++)
  {
    if(para[i] == '/' && para[++i] == 's')
    {
      paraType = 1;
      break;
    }
    else if(para[i] != '\0' && para[i] == 'a' && para[++i] == 'd')
    {
      paraType = 2;
      break;
    }
  }

  switch(paraType)
  {
  case 0://û�в���
    if(this->path1Type == 0)//���·��
    {
      //��λ������·��:����workingPath���ҵ���ǰ·��
      this->GotoRelativeSearchPosition(&curPosition, workingPath, &flag);
    }
    else if(this->path1Type == 1)//����·��
    {
      //����pathElesList����λ����Ӧ·��
      this->GotoAbsoluteSearchPosition(&curPosition, &flag);
    }

    //��ʾ��ǰ�ļ����µ������ļ����ļ���
    DisplayChildrenNode(curPosition, flag);
    break;
  case 1://����Ϊ/s
    if(this->path1Type == 0)//���·��
    {
      //����workingPath,��λ����ǰ·��
      this->GotoRelativeSearchPosition(&curPosition, workingPath, &flag);
    }
    else if(this->path1Type == 1)//����·��
    {
       //����pathElesList����λ����Ӧ·��
       this->GotoAbsoluteSearchPosition(&curPosition, &flag);
    }

    //������ȱ�������ʾ��Ӧ·����ÿһ���ļ��е������ļ����ļ���
    this->DisplayAll(curPosition, flag);

    break;
  case 2://����Ϊ/ad
    if(this->path1Type == 0)//���·��
    {
      //��λ������·��:����workingPath���ҵ���ǰ·��
      this->GotoRelativeSearchPosition(&curPosition, workingPath, &flag);
    }
    else if(this->path1Type == 1)//����·��
    {
      //����pathElesList����λ����Ӧ·��
      this->GotoAbsoluteSearchPosition(&curPosition, &flag);
    }

    //��ʾ��ǰ�ļ����µ������ļ����ļ���
    this->DisplayChildrenFold(curPosition, flag);

    break;
  case -1://�������ʹ���
  default:
    std::cout << "�������ʹ���\n" <<std::endl;
    flag = false;
  }

  if(!flag)
  {
    std::cout << "δ�ҵ�ָ��Ŀ¼" << std::endl;
  }
  return flag;
}

//��λ�����·���µĴ���ѯ�ļ�����
void DirCmd::GotoRelativeSearchPosition(DirObject** curPosition, MyList<DirObject>* workingPath, bool* flag)
{
  MyString tempDirName;               //Ŀ¼����
  DirObject* dirNode = NULL;          //��ʱ����DirObject����

  //��λ������·��:����workingPath���ҵ���ǰ·��
  workingPath->InitList();
  while(workingPath->GetNextNode() != NULL)
  {
    tempDirName = workingPath->GetCurNode()->GetDirName();
    (*curPosition) = (*curPosition)->Find(tempDirName);
    if((*curPosition) == NULL)
    {
      (*flag) = false;
      break;
    }
  }
  //��������ҵ�Ŀ¼
  if(*flag)
  {
    this->pathElesList.InitList();
    while(this->pathElesList.GetCurNode() != NULL)
    {
      tempDirName = pathElesList.GetCurNode()->GetDirName();
      (*curPosition) = (*curPosition)->Find(tempDirName);
      if((*curPosition) == NULL)
      {
        (*flag) = false;
        break;
      }
      pathElesList.GetNextNode();
    }
  }
}

//��λ������·���µĴ���ѯ�ļ�����
void DirCmd::GotoAbsoluteSearchPosition(DirObject** curPosition, bool* flag)
{
  MyString tempDirName;               //Ŀ¼����
  DirObject* dirNode = NULL;          //��ʱDirObject����

  //����pathElesList����λ����Ӧ·��
  pathElesList.InitList();
  while(pathElesList.GetNextNode() != NULL)
  {
    tempDirName = pathElesList.GetCurNode()->GetDirName();
    if((*curPosition)->Find(tempDirName)!=NULL)
    {
      //������һĿ¼
      (*curPosition) = (*curPosition)->Find(tempDirName);
    }
    else
    {
      (*flag) = false;
      break;
    }
  }
}

//��ʾ��ǰ�ļ����µ������ļ����ļ���
void DirCmd::DisplayChildrenNode(DirObject* curPosition, bool flag)
{
  if(flag)
  {
    curPosition->childrenLink.InitList();
    while(curPosition->childrenLink.GetCurNode() != NULL)
    {
      std::cout << curPosition->childrenLink.GetCurNode()->GetDirName().data << std::endl;
      curPosition->childrenLink.GetNextNode();
    }
  }
}

//��ʾ��ǰ�ļ����µ������ļ���
void DirCmd::DisplayChildrenFold(DirObject* curPosition, bool flag)
{
  if(flag)
  {
    curPosition->childrenLink.InitList();
    while(curPosition->childrenLink.GetCurNode() != NULL)
    {
      if(curPosition->childrenLink.GetCurNode()->GetTypeFlag() == 0)
      {
        std::cout << curPosition->childrenLink.GetCurNode()->GetDirName().data << std::endl;
      }
      curPosition->childrenLink.GetNextNode();
    }
  }
}

//��ʾ��ǰ�ļ����²�������ļ��е�����
void DirCmd::DisplayAll(DirObject* curPosition, bool flag)
{
  /*��ʾ��ʽ��
    C:\test1��Ŀ¼��
    test11
    test12
    testfile11.txt
  */

}
void DirCmd::SetPath1Type(int path1Type)
{
  this->path1Type = path1Type;
}

int DirCmd::GetPath1Type()
{
  return path1Type;
}