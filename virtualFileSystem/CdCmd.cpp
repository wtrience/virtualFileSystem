
#include "CdCmd.h"

bool CdCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;
  
  DirObject* curPosition = rootDir;
  DirObject* dirNode = NULL;
  MyString tempDirName;

  //·������
  int dirType = this->path1Type;
  switch(dirType)
  {
  case msg.FLOD_PATH://���·��
    //����workingPath,��λ����ǰĿ¼
    workingPath->InitList();
    while(workingPath->GetNextNode() != NULL)
    {
      tempDirName = workingPath->GetCurNode()->GetDirName();
      curPosition = curPosition->Find(tempDirName);
      if(curPosition == NULL)
      {
        flag = false;
        break;
      }
    }
    //����pathElesList,�ҵ�ָ��λ�ã�û���ҵ�������false
    if(flag)
    {
      pathElesList.InitList();
      while(pathElesList.GetCurNode() != NULL)
      {
        tempDirName = pathElesList.GetCurNode()->GetDirName();
        if(curPosition->Find(tempDirName)!=NULL)
        {
          //���¹���Ŀ¼
          DirObject* dirNode = new VirtualFold(tempDirName);
          workingPath->AddNode(*dirNode);
        }
        else
        {
          //·��������
          flag = false;
          break;
        }
        pathElesList.GetNextNode();
      }
    }
    break;
  case msg.FLOD_WHOLE_PATH://����·��
    workingPath->Empty();

    pathElesList.InitList();
    //����̷�
    tempDirName = pathElesList.GetCurNode()->GetDirName();
    dirNode = new VirtualFold(tempDirName);
    workingPath->AddNode(*dirNode);

    while(pathElesList.GetNextNode() != NULL)
    {
      tempDirName = pathElesList.GetCurNode()->GetDirName();
      if(curPosition->Find(tempDirName)!=NULL)
      {
        //����Ŀ¼
        dirNode= new VirtualFold(tempDirName);
        workingPath->AddNode(*dirNode);

        curPosition = curPosition->Find(tempDirName);
      }
      else
      {
        flag = false;
        break;
      }
    }
    break;
  case msg.BACK_TO_PARENT://���ص���һĿ¼ 
    workingPath->InitList();
    while(workingPath->GetNextNode() != NULL)
    {
      dirNode = workingPath->GetCurNode();
    }
    workingPath->DelNode(*dirNode);

    break;

  case msg.BACK_TO_ROOT://���ص���Ŀ¼
    workingPath->InitList();
    //����̷�
    tempDirName = workingPath->GetCurNode()->GetDirName();
    dirNode = new VirtualFold(tempDirName);
    workingPath->Empty();
    workingPath->AddNode(*dirNode);
    break;
  default:
    flag = false;
  }  

  if(flag)
  {
    std::cout << "����ִ�гɹ�" << std::endl;
  }
  else
  {
    std::cout << "����ִ��ʧ��" << std::endl;
  }
  return flag;
}
void CdCmd::SetPath1Type(int path1Type)
{
  this->path1Type = path1Type;
}

int CdCmd::GetPath1Type()
{
  return path1Type;
}