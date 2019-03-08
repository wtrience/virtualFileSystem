
#include "MkdirCmd.h"

bool MkdirCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;
  MyString tempDirName;
  DirObject* curPosition = rootDir;

  int pathType = this->path1Type;
  switch(pathType)
  {
  case 0://相对路径:
    //定位到工作路径:遍历workingPath，找到当前路径
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
    //创建目录:遍历pathElesList，创建目录
    if(flag)
    {
      pathElesList.InitList();
      while(pathElesList.GetCurNode() != NULL)
      {
        tempDirName = pathElesList.GetCurNode()->GetDirName();
        if(curPosition->Find(tempDirName)==NULL)
        {
          //创建目录
          DirObject* dirNode = new VirtualFold(tempDirName);
          curPosition->AddDirNode(dirNode);
          pathElesList.GetNextNode();
        }
        else
        {
          //查找下一目录
          if(pathElesList.GetNextNode()!=NULL)
          {
            curPosition = curPosition->Find(tempDirName);
          }
          else
          {
            flag = false;
            std::cout << tempDirName.data << "文件夹已经存在" << std::endl;
            break;
          }
          
        }
      }
    }

    break;
  case 1://绝对路径：根据root，一级一级查找添加
    pathElesList.InitList();
    while(pathElesList.GetNextNode() != NULL)
    {
      tempDirName = pathElesList.GetCurNode()->GetDirName();
      if(curPosition->Find(tempDirName)==NULL)
      {
        //创建目录
        DirObject* dirNode = new VirtualFold(tempDirName);
        curPosition->AddDirNode(dirNode);
      }
      else
      {
        //查找下一目录
        if(pathElesList.GetNextNode()!=NULL)
        {
          curPosition = curPosition->Find(tempDirName);
        }
        else
        {
          flag = false;
          std::cout << tempDirName.data << "文件夹已经存在" << std::endl;
          break;
        }
      }
    }
    break;
  }

  if(flag)
  {
    std::cout << "目录创建成功！" << std::endl;
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