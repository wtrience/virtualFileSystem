
#include "DelCmd.h"

bool DelCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;                   //记录命令是否执行成功
  MyString tempDirName;               //目录名称
  DirObject* curPosition = rootDir;   //记录当前位置
  DirObject* dirNode = NULL;          //临时不错DirObject对象
  int delFileNum;

  //解析路径类型
  int pathType = this->GetPath1Type();
  switch(pathType)
  {
  case msg.FILE_PATH://删除相对路径下指定的文件
    //定位到待删除文件对应的文件夹
    this->GotoRelativePreFlodPosition(&curPosition, workingPath, &tempDirName, &flag);

    //删除文件
    if(flag)
    {
      dirNode = curPosition->Find(tempDirName);
      if(dirNode == NULL)
      {
        std::cout<< "文件不存在，无法删除！" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        curPosition->childrenLink.DelNode(*dirNode);
        std::cout << "文件已删除！" << std::endl;
      }
    }
    else
    {
      std::cout << "文件不存在，无法删除！" << std::endl;
    }
    break;
  case msg.FILE_WHOLE_PATH:
    //定位到待删除文件对应的文件夹
    GotoAbsolutePreFlodPosition(&curPosition, &tempDirName, &flag);

    //删除文件
    if(flag)
    {
      dirNode = curPosition->Find(tempDirName);
      if(dirNode == NULL)
      {
        std::cout<< "文件不存在，无法删除！" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        curPosition->childrenLink.DelNode(*dirNode);
        std::cout << "文件已删除！" << std::endl;
      }
    }
    else
    {
      std::cout << "文件不存在，无法删除！" << std::endl;
    }
    break;
  case msg.FLOD_PATH:
    //相对路径：定位到对应的文件夹
    GotoRelativeFoldPosition(&curPosition, workingPath, &flag);

    if(flag)
    {
      //删除文件夹下的所有文件
      DelAllFile(&curPosition, &flag);
      if(flag)
      {
        std::cout << "文件已删除！" << std::endl;
      }
      else
      {
        std::cout << "该文件夹下没有文件！" << std::endl;
      }
    }
    else
    {
      std::cout << "路径不存在，无法删除！" << std::endl;
    }
    break;
  case msg.FLOD_WHOLE_PATH:
    //绝对路径：定位到对应的文件夹
    this->GotoAbsoluteFoldPosition(&curPosition, &flag);
    
    if(flag)
    {
      //删除文件夹下的所有文件
      DelAllFile(&curPosition, &flag);
      if(flag)
      {
        std::cout << "文件已删除！" << std::endl;
      }
      else
      {
        std::cout << "该文件夹下没有文件！" << std::endl;
      }
    }
    else
    {
      std::cout << "路径不存在，无法删除！" << std::endl;
    }

    break;
  case msg.WILDCARD:
    
    this->pathElesList.InitList();
    if(this->pathElesList.GetCurNode() != NULL)
    {
      MyString dirName;
      //找到上一目录文件夹
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &dirName, &flag);

      /*当通配符为星号的时候，删除当前文件夹下的所有文件*/
      //MyString dirName = this->pathElesList.GetCurNode()->GetDirName();
      MyString star("*");

      if(star == dirName)
      {
        //删除当前文件夹下的所有文件
        DelAllFile(&curPosition, &flag);
        std::cout << curPosition->GetDirName().data << "下所有文件已删除！" << std::endl;
      }
      /*当为问号的时候，遍历所有文件，对文件名逐个进行比对*/
      else 
      {
        int delFileNum = 0;
        curPosition->childrenLink.InitList();
        while(curPosition->childrenLink.GetCurNode() != NULL)
        {
          MyString fileName;
          if(curPosition->childrenLink.GetCurNode()->GetTypeFlag() == 1)
          {
            fileName = curPosition->childrenLink.GetCurNode()->GetDirName();
            bool isExist = true;
            for(int index=0;  fileName.data[index] != '\0' && dirName.data[index] != '\0'; index++)
            {
              if(dirName.data[index] == '?')
              {
                continue;
              }
              else if(dirName.data[index] != fileName.data[index])
              {
                isExist = false;
                break;
              }
            }

            if(isExist)
            {
              //删除之
              DirObject* dirNode = curPosition->Find(fileName);
              curPosition->childrenLink.DelNode(*dirNode);
              std::cout << fileName.data << "文件已删除！" << std::endl;
              delFileNum++;
            }
          }
          curPosition->childrenLink.GetNextNode();
        }

        if(delFileNum == 0)
        { 
          std::cout << "没有找到匹配的文件！" << std::endl;
          flag = false;
          break;
        }
      }
    }
    else
    {
      std::cout << "路径为空，命令无法执行！" << std::endl;
      flag = false;
    }
    break;
  case msg.WILDCARD_WHOLE:
    this->GotoAbsolutePreFlodPosition(&curPosition, &tempDirName, &flag);

    delFileNum = 0;
    curPosition->childrenLink.InitList();
    while(curPosition->childrenLink.GetCurNode() != NULL)
    {
      MyString fileName;
      if(curPosition->childrenLink.GetCurNode()->GetTypeFlag() == 1)
      {
        fileName = curPosition->childrenLink.GetCurNode()->GetDirName();
        bool isExist = true;
        for(int index=0;  fileName.data[index] != '\0' && tempDirName.data[index] != '\0'; index++)
        {
          if(tempDirName.data[index] == '?')
          {
            continue;
          }
          else if(tempDirName.data[index] != fileName.data[index])
          {
            isExist = false;
            break;
          }
        }

        if(isExist)
        {
          //删除之
          DirObject* dirNode = curPosition->Find(fileName);
          curPosition->childrenLink.DelNode(*dirNode);
          std::cout << fileName.data << "文件已删除！" << std::endl;
          delFileNum++;
        }
      }
      curPosition->childrenLink.GetNextNode();
    }

    if(delFileNum == 0)
    { 
      std::cout << "没有找到匹配的文件！" << std::endl;
      flag = false;
      break;
    }
    break;
  default:
    std::cout << "命令格式错误！" << std::endl;
    flag = false;
  }

  return flag;
}

//定位到指定文件夹
void DelCmd::GotoAbsoluteFoldPosition(DirObject** curPosition, bool* flag)
{
  MyString tempDirName;

  pathElesList.InitList();

  while(pathElesList.GetNextNode() != NULL)
  {
    tempDirName = pathElesList.GetCurNode()->GetDirName();
    if((*curPosition)->Find(tempDirName)!=NULL)
    {
      (*curPosition) = (*curPosition)->Find(tempDirName);
    }
    else
    {
      (*flag) = false;
      break;
    }
  }
}

void DelCmd::GotoRelativeFoldPosition(DirObject** curPosition, MyList<DirObject>* workingPath, bool* flag)
{
  MyString tempDirName;

  //遍历workingPath,定位到当前目录
  workingPath->InitList();
  while(workingPath->GetNextNode() != NULL)
  {
    tempDirName = workingPath->GetCurNode()->GetDirName();
    (*curPosition) = (*curPosition)->Find(tempDirName);
    if(curPosition == NULL)
    {
      (*flag) = false;
      break;
    }
  }
  //遍历pathElesList,找到指定位置，没有找到，返回false
  if((*flag))
  {
    pathElesList.InitList();
    while(pathElesList.GetCurNode() != NULL)
    {
      tempDirName = pathElesList.GetCurNode()->GetDirName();
      if((*curPosition)->Find(tempDirName)!=NULL)
      {
        //查找下一目录
        (*curPosition) = (*curPosition)->Find(tempDirName);
      }
      else
      {
        //路径不存在
        (*flag) = false;
        break;
      }
      pathElesList.GetNextNode();
    }
  }
}

//文件的相对路径定位
void DelCmd::GotoRelativePreFlodPosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* delDirName, bool* flag)
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

//文件的绝对路径定位
void DelCmd::GotoAbsolutePreFlodPosition(DirObject** curPosition, MyString* delDirName, bool* flag)
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

//删除文件夹下的所有文件
void DelCmd::DelAllFile(DirObject** curPosition, bool* flag)
{
  (*flag) = false;

  (*curPosition)->childrenLink.InitList();
  while((*curPosition)->childrenLink.GetCurNode() != NULL)
  {
    if((*curPosition)->childrenLink.GetCurNode()->GetTypeFlag() == 1)
    {
      DirObject* fileNode = (*curPosition)->childrenLink.GetCurNode();
      (*curPosition)->childrenLink.DelNode(*fileNode);
      (*flag) = true;
    }
    else
    {
      (*curPosition)->childrenLink.GetNextNode();
    }
  }
}
void DelCmd::SetPath1Type(int path1Type)
{
  this->path1Type = path1Type;
}

int DelCmd::GetPath1Type()
{
  return path1Type;
}