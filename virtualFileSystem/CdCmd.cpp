
#include "CdCmd.h"

bool CdCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;
  
  DirObject* curPosition = rootDir;
  DirObject* dirNode = NULL;
  MyString tempDirName;

  //路径类型
  int dirType = this->path1Type;
  switch(dirType)
  {
  case msg.FLOD_PATH://相对路径
    //遍历workingPath,定位到当前目录
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
    //遍历pathElesList,找到指定位置，没有找到，返回false
    if(flag)
    {
      pathElesList.InitList();
      while(pathElesList.GetCurNode() != NULL)
      {
        tempDirName = pathElesList.GetCurNode()->GetDirName();
        if(curPosition->Find(tempDirName)!=NULL)
        {
          //更新工作目录
          DirObject* dirNode = new VirtualFold(tempDirName);
          workingPath->AddNode(*dirNode);
        }
        else
        {
          //路径不存在
          flag = false;
          break;
        }
        pathElesList.GetNextNode();
      }
    }
    break;
  case msg.FLOD_WHOLE_PATH://绝对路径
    workingPath->Empty();

    pathElesList.InitList();
    //添加盘符
    tempDirName = pathElesList.GetCurNode()->GetDirName();
    dirNode = new VirtualFold(tempDirName);
    workingPath->AddNode(*dirNode);

    while(pathElesList.GetNextNode() != NULL)
    {
      tempDirName = pathElesList.GetCurNode()->GetDirName();
      if(curPosition->Find(tempDirName)!=NULL)
      {
        //创建目录
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
  case msg.BACK_TO_PARENT://返回到上一目录 
    workingPath->InitList();
    while(workingPath->GetNextNode() != NULL)
    {
      dirNode = workingPath->GetCurNode();
    }
    workingPath->DelNode(*dirNode);

    break;

  case msg.BACK_TO_ROOT://返回到根目录
    workingPath->InitList();
    //添加盘符
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
    std::cout << "命令执行成功" << std::endl;
  }
  else
  {
    std::cout << "命令执行失败" << std::endl;
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