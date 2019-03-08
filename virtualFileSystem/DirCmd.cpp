
#include "DirCmd.h"

DirCmd::DirCmd()
{
  for(int i=0; i<PARASIZE; i++)
    para[i] = '\0';
}

bool DirCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;                   //记录命令是否执行成功
  DirObject* curPosition = rootDir;   //记录当前位置
  DirObject* dirNode = NULL;          //临时不错DirObject对象

  //解析参数类型
  int paraType = -1;
  if(para[0] == '\0')//参数为空时，paraType为0
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
  case 0://没有参数
    if(this->path1Type == 0)//相对路径
    {
      //定位到工作路径:遍历workingPath，找到当前路径
      this->GotoRelativeSearchPosition(&curPosition, workingPath, &flag);
    }
    else if(this->path1Type == 1)//绝对路径
    {
      //遍历pathElesList，定位到对应路径
      this->GotoAbsoluteSearchPosition(&curPosition, &flag);
    }

    //显示当前文件夹下的所有文件和文件夹
    DisplayChildrenNode(curPosition, flag);
    break;
  case 1://参数为/s
    if(this->path1Type == 0)//相对路径
    {
      //遍历workingPath,定位到当前路径
      this->GotoRelativeSearchPosition(&curPosition, workingPath, &flag);
    }
    else if(this->path1Type == 1)//绝对路径
    {
       //遍历pathElesList，定位到对应路径
       this->GotoAbsoluteSearchPosition(&curPosition, &flag);
    }

    //深度优先遍历，显示对应路径下每一个文件夹的所有文件和文件夹
    this->DisplayAll(curPosition, flag);

    break;
  case 2://参数为/ad
    if(this->path1Type == 0)//相对路径
    {
      //定位到工作路径:遍历workingPath，找到当前路径
      this->GotoRelativeSearchPosition(&curPosition, workingPath, &flag);
    }
    else if(this->path1Type == 1)//绝对路径
    {
      //遍历pathElesList，定位到对应路径
      this->GotoAbsoluteSearchPosition(&curPosition, &flag);
    }

    //显示当前文件夹下的所有文件和文件夹
    this->DisplayChildrenFold(curPosition, flag);

    break;
  case -1://参数类型错误
  default:
    std::cout << "参数类型错误！\n" <<std::endl;
    flag = false;
  }

  if(!flag)
  {
    std::cout << "未找到指定目录" << std::endl;
  }
  return flag;
}

//定位到相对路径下的待查询文件夹下
void DirCmd::GotoRelativeSearchPosition(DirObject** curPosition, MyList<DirObject>* workingPath, bool* flag)
{
  MyString tempDirName;               //目录名称
  DirObject* dirNode = NULL;          //临时不错DirObject对象

  //定位到工作路径:遍历workingPath，找到当前路径
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
  //进入待查找的目录
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

//定位到绝对路径下的待查询文件夹下
void DirCmd::GotoAbsoluteSearchPosition(DirObject** curPosition, bool* flag)
{
  MyString tempDirName;               //目录名称
  DirObject* dirNode = NULL;          //临时DirObject对象

  //遍历pathElesList，定位到对应路径
  pathElesList.InitList();
  while(pathElesList.GetNextNode() != NULL)
  {
    tempDirName = pathElesList.GetCurNode()->GetDirName();
    if((*curPosition)->Find(tempDirName)!=NULL)
    {
      //查找下一目录
      (*curPosition) = (*curPosition)->Find(tempDirName);
    }
    else
    {
      (*flag) = false;
      break;
    }
  }
}

//显示当前文件夹下的所有文件和文件夹
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

//显示当前文件夹下的所有文件夹
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

//显示当前文件夹下层的所有文件夹的内容
void DirCmd::DisplayAll(DirObject* curPosition, bool flag)
{
  /*显示格式：
    C:\test1的目录：
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