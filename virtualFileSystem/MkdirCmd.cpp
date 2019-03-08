
#include "MkdirCmd.h"

bool MkdirCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;
  MyString tempDirName;
  DirObject* curPosition = rootDir;

  int pathType = this->path1Type;
  switch(pathType)
  {
  case 0://���·��:
    //��λ������·��:����workingPath���ҵ���ǰ·��
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
    //����Ŀ¼:����pathElesList������Ŀ¼
    if(flag)
    {
      pathElesList.InitList();
      while(pathElesList.GetCurNode() != NULL)
      {
        tempDirName = pathElesList.GetCurNode()->GetDirName();
        if(curPosition->Find(tempDirName)==NULL)
        {
          //����Ŀ¼
          DirObject* dirNode = new VirtualFold(tempDirName);
          curPosition->AddDirNode(dirNode);
          pathElesList.GetNextNode();
        }
        else
        {
          //������һĿ¼
          if(pathElesList.GetNextNode()!=NULL)
          {
            curPosition = curPosition->Find(tempDirName);
          }
          else
          {
            flag = false;
            std::cout << tempDirName.data << "�ļ����Ѿ�����" << std::endl;
            break;
          }
          
        }
      }
    }

    break;
  case 1://����·��������root��һ��һ���������
    pathElesList.InitList();
    while(pathElesList.GetNextNode() != NULL)
    {
      tempDirName = pathElesList.GetCurNode()->GetDirName();
      if(curPosition->Find(tempDirName)==NULL)
      {
        //����Ŀ¼
        DirObject* dirNode = new VirtualFold(tempDirName);
        curPosition->AddDirNode(dirNode);
      }
      else
      {
        //������һĿ¼
        if(pathElesList.GetNextNode()!=NULL)
        {
          curPosition = curPosition->Find(tempDirName);
        }
        else
        {
          flag = false;
          std::cout << tempDirName.data << "�ļ����Ѿ�����" << std::endl;
          break;
        }
      }
    }
    break;
  }

  if(flag)
  {
    std::cout << "Ŀ¼�����ɹ���" << std::endl;
  }
  return flag;
}

void MkdirCmd::SetPath1Type(int path1Type)
{
  this->path1Type = path1Type;
}

int MkdirCmd::GetPath1Type()
{
  return path1Type;
}