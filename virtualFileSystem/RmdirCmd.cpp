
#include "RmdirCmd.h"

RmdirCmd::RmdirCmd()
{
  for(int i=0; i<PARASIZE; i++)
    para[i] = '\0';
}

bool RmdirCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;                   //记录命令是否执行成功
  MyString delDirName;               //目录名称
  DirObject* curPosition = rootDir;   //记录当前位置
  DirObject* dirNode = NULL;          //临时不错DirObject对象

  //解析参数类型
  int paraType = -1;
  if(para[0] == '\0')//参数为空时，paraType为0
    paraType = 0;     

  for(int i=0; para[i] != '\0'; i++)
  {
    if(para[i] == '/' && para[i+1] == 's' && para[i+2] == '\0')
    {
      paraType = 1;
      break;
    }
    else if(para[i] == '/' && para[i+1] == 's' && para[i+2] == '/' && para[i+3] == 'q')
    {
      paraType = 2;
      break;
    }
  }

  switch(paraType)
  {
  case 0://无参数
    //找到该文件夹的上一层目录地址
    if(this->path1Type == 0)//相对目录
    {
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &delDirName, &flag);
    }
    else if(this->path1Type == 1)//绝对路径
    {
      this->GotoAbsolutePreFlodPosition(&curPosition, &delDirName, &flag);
    }
    //查看该文件夹是否为空，是，删除，否，提示文件夹不为空，无法删除
    if(flag)
    {
      dirNode = curPosition->Find(delDirName);
      if(dirNode == NULL)
      {
        std::cout<< "文件夹不存在，无法删除！" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        if(dirNode->childrenLink.GetCurNode() == NULL)
        {
          curPosition->childrenLink.DelNode(*dirNode);
          std::cout << "文件夹已删除！" << std::endl;
        }
        else
        {
          flag = false;
          std::cout << "文件夹非空，无法删除文件夹！"<< std::endl;
        }
      }
    }
    else
    {
      std::cout << "文件夹不存在，删除失败!" << std::endl;
    }
    break;
  case 1://参数为/s，用于指定删除整个文件夹
    //找到该文件夹的上一层目录地址
    if(this->path1Type == 0)//相对目录
    {
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &delDirName, &flag);
    }
    else if(this->path1Type == 1)//绝对路径
    {
      this->GotoAbsolutePreFlodPosition(&curPosition, &delDirName, &flag);
    }
    //查看该文件夹是否为空，是，删除，否，询问用户是否删除
    if(flag)
    {
      dirNode = curPosition->Find(delDirName);
      if(dirNode == NULL)
      {
        std::cout<< "文件夹不存在，无法删除！" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        if(dirNode->childrenLink.GetCurNode() == NULL)
        {
          curPosition->childrenLink.DelNode(*dirNode);
          std::cout << "文件夹已删除！" << std::endl;
        }
        else
        {
          std::cout << "文件夹非空，确定要删除文件夹（y/n）:";
          while(1)
          {
            char delCmd;
            std::cin >> delCmd;
            if(delCmd == 'y' || delCmd == 'Y')
            {
              curPosition->childrenLink.DelNode(*dirNode);
              std::cout << "文件夹已删除！" << std::endl;
              break;
            }
            else if(delCmd == 'n' || delCmd == 'N')
            {
              std::cout << "文件夹未删除！" << std::endl;
              break;
            }
            std::cout <<"请确定是否删除文件夹：y为确定，n为取消" << std::endl;
          }
        }
      }
    }
    else
    {
      std::cout << "文件夹不存在，删除失败！" << std::endl;
    }
    break;
  case 2://参数为/s/q，用于指定以不询问的状态删除整个文件夹
    //找到该文件夹的上一层目录地址
    if(this->path1Type == 0)//相对目录
    {
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &delDirName, &flag);
    }
    else if(this->path1Type == 1)//绝对路径
    {
      this->GotoAbsolutePreFlodPosition(&curPosition, &delDirName, &flag);
    }
    //删除整个文件夹
    if(flag)
    {
      dirNode = curPosition->Find(delDirName);
      if(dirNode == NULL)
      {
        std::cout<< "文件夹不存在，无法删除！" << std::endl;
        flag = false;
      }
      else
      {
        curPosition->childrenLink.DelNode(*dirNode);
        std::cout << "文件夹已删除！" << std::endl;
      }
    }
    else
    {
      std::cout << "文件夹删除失败!" << std::endl;
    }
    break;
  case -1:
  default:
    std::cout << "参数类型错误！\n" <<std::endl;
  }

  return false;
}

//相对路径定位
void RmdirCmd::GotoRelativePreFlodPosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* delDirName, bool* flag)
{
  DirObject* dirNodePar  = NULL;      //临时Parent对象
  
  workingPath->InitList();
  dirNodePar = workingPath->GetCurNode();
  while(workingPath->GetNextNode() != NULL)
  {
    (*delDirName) = workingPath->GetCurNode()->GetDirName();
    dirNodePar = (*curPosition);
    if((*curPosition)->Find((*delDirName))!=NULL)
    {
      //查找下一目录
      (*curPosition) = (*curPosition)->Find((*delDirName));
    }
    else
    {
      (*flag) = false;
      break;
    }
  }

  this->pathElesList.InitList();

  if(this->pathElesList.GetCurNode() == NULL)//若pathElesList为空，则是workingPath的倒数第二层目录
  {
    (*flag) = false;
  }
  else if(this->pathElesList.GetNextNode() == NULL)//如果pathElesList只有一个元素，则为workingPath目录
  {
    //获得待删除文件夹的文件夹名
    this->pathElesList.InitList();
    (*delDirName) = this->pathElesList.GetCurNode()->GetDirName();  
  }
  else//若pathElesList有两个以上元素，则为workingPath目录
  {
    //pathElesList的倒数第二层目录
    DirObject* dirNodePar  = NULL;      //临时Parent对象

    //遍历pathElesList，定位到对应路径
    pathElesList.InitList();
    while(pathElesList.GetCurNode() != NULL)
    {
      (*delDirName) = pathElesList.GetCurNode()->GetDirName();
      dirNodePar = (*curPosition);
      if((*curPosition)->Find((*delDirName))!=NULL)
      {
        //查找下一目录
        (*curPosition) = (*curPosition)->Find((*delDirName));
      }
      else
      {
        (*flag) = false;
        break;
      }
      pathElesList.GetNextNode();
    }
    //返回到上一目录
    (*curPosition) = dirNodePar;
  }
}

//绝对路径定位
void RmdirCmd::GotoAbsolutePreFlodPosition(DirObject** curPosition, MyString* delDirName, bool* flag)
{
  //pathElesList的倒数第二层目录

  DirObject* dirNodePar  = NULL;      //临时Parent对象

  //遍历pathElesList，定位到对应路径
  pathElesList.InitList();
  dirNodePar = pathElesList.GetCurNode();
  while(pathElesList.GetNextNode() != NULL)
  {
    (*delDirName) = pathElesList.GetCurNode()->GetDirName();
    dirNodePar = (*curPosition);
    if((*curPosition)->Find((*delDirName))!=NULL)
    {
      //查找下一目录
      (*curPosition) = (*curPosition)->Find((*delDirName));
    }
    else
    {
      (*flag) = false;
      break;
    }

  }
  //返回到上一目录
  (*curPosition) = dirNodePar;
} 

void RmdirCmd::SetPath1Type(int path1Type)
{
  this->path1Type = path1Type;
}

int RmdirCmd::GetPath1Type()
{
  return path1Type;
}