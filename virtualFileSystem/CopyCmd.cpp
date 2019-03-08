
#include "CopyCmd.h"

bool CopyCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;
  MyString tempDirName;               //目录名称
  DirObject* curPosition = rootDir;   //记录当前位置
  DirObject* dirNode = NULL;          //临时不错DirObject对象

  DirObject* cur1Position = rootDir;  //记录path1当前位置
  DirObject* cur2Position = rootDir;  //记录path2当前位置

  MyString path1Name;     //记录path1的名称
  MyString path2Name;     //记录path2的名称

  VirtualFile* file1;     //file1对象
  VirtualFile* file2;     //file2对象

  int path1Type = this->GetPath1Type();
  int path2Type = this->GetPath2Type();

  //将文件夹复制给文件
  if((path1Type == msg.FLOD_PATH || path1Type == msg.FLOD_WHOLE_PATH) && (path2Type == msg.FILE_PATH || path2Type == msg.FILE_WHOLE_PATH))
  {
    std::cout << "无法将文件夹复制给文件！" << std::endl;
    flag = false;
  }

  //将文件夹复制给文件夹
  else if((path1Type == msg.FLOD_PATH || path1Type == msg.FLOD_WHOLE_PATH) && (path2Type == msg.FLOD_PATH || path2Type == msg.FLOD_WHOLE_PATH))
  {
    //定位到path1ElesList对应的路径
    switch(path1Type)
    {
    case msg.FLOD_PATH:
      this->GotoRelativeFoldPosition(&cur1Position, workingPath, 1, &flag);
      break;
    case msg.FLOD_WHOLE_PATH:
      this->GotoAbsoluteFoldPosition(&cur1Position,1, &flag);
      break;
    default:
      std::cout << "待复制的路径名错误！" << std::endl;
      flag = false;
    }

    //定位到path2ElesList对应的路径
    switch(path2Type)
    {
    case msg.FLOD_PATH:
      this->GotoRelativeFoldPosition(&cur2Position, workingPath, 2, &flag);
      break;
    case msg.FLOD_WHOLE_PATH:
      this->GotoAbsoluteFoldPosition(&cur2Position, 2, &flag);
      break;
    default:
      std::cout << "待复制的路径名错误！" << std::endl;
      flag = false;
    }

    //将path1文件夹下的所有文件复制到path2中，并判断path2中是否存在该名称的文件，存在，则询问是否覆盖，否则，直接复制
    CopyAllFile(cur1Position, &cur2Position, &flag);

  }

  //将文件复制给文件夹
  else if((path1Type == msg.FILE_PATH || path1Type == msg.FILE_WHOLE_PATH) && (path2Type == msg.FLOD_PATH || path2Type == msg.FLOD_WHOLE_PATH))
  {
    //找到file1
    switch(path1Type)
    {
    case msg.FILE_PATH://相对路径
      this->GotoFileRelativePosition(&cur1Position, workingPath, &path1Name, 1, &flag);
      break;
    case msg.FILE_WHOLE_PATH://绝对路径
      this->GotoFileAbsolutePosition(&cur1Position, &path1Name, 1, &flag);
      break;
    default:
      std::cout << "待复制的路径名错误！" << std::endl;
      flag = false;
    }
    //获得文件对象
    if(flag)
    {
      file1 = (VirtualFile*)cur1Position->Find(path1Name);
      if(file1 == NULL)
      {
        std::cout << path1Name.data << "文件不存在!" << std::endl;
        flag = false;
      }
    }
    //定位到path2ElesList对应的路径
    switch(path2Type)
    {
    case msg.FLOD_PATH:
      this->GotoRelativeFoldPosition(&cur2Position, workingPath, 2, &flag);
      break;
    case msg.FLOD_WHOLE_PATH:
      this->GotoAbsoluteFoldPosition(&cur2Position, 2, &flag);
      break;
    default:
      std::cout << "待复制的路径名错误！" << std::endl;
      flag = false;
    }

    //将文件复制到path2中，并判断path2中是否存在该名称的文件，存在，则询问是否覆盖，否则，直接复制
    if(flag)
    {
      if(cur2Position->Find(path1Name) == NULL)
      {
        VirtualFile* copyFile = new VirtualFile(path1Name);
        copyFile->Copy(file1);
        cur2Position->AddDirNode(copyFile);
        std::cout << "已成功将" << path1Name.data << "复制到" << cur2Position->GetDirName().data << "文件夹中" << std::endl;
      }
      else
      {
        std::cout << "文件已经存在，是否将其覆盖(y/n):";
        while(1)
        {
          char copyCmd;
          std::cin >> copyCmd;
          if(copyCmd == 'y' || copyCmd == 'Y')
          {
            file2 = (VirtualFile*)cur2Position->Find(path1Name);
            file2->Copy(file1);
            std::cout << "文件已覆盖！" << std::endl;
            break;
          }
          else if(copyCmd == 'n' || copyCmd == 'N')
          {
            std::cout << "文件未覆盖！" << std::endl;
            break;
          }
          std::cout <<"请确定是否覆盖文件：y为确定，n为取消" << std::endl;
        }
      }
    }

  }

  //将文件复制给文件
  else if((path1Type == msg.FILE_PATH || path1Type == msg.FILE_WHOLE_PATH) && (path2Type == msg.FILE_PATH || path2Type == msg.FILE_WHOLE_PATH))
  {
    //找到file1
    switch(path1Type)
    {
    case msg.FILE_PATH:
      this->GotoFileRelativePosition(&cur1Position, workingPath, &path1Name, 1, &flag);
      break;
    case msg.FILE_WHOLE_PATH:
      this->GotoFileAbsolutePosition(&cur1Position, &path1Name, 1, &flag);
      break;
    default:
      std::cout << "待复制的路径名错误！" << std::endl;
      flag = false;
    }

    //获得文件对象
    if(flag)
    {
      file1 = (VirtualFile*)cur1Position->Find(path1Name);
      if(file1 == NULL)
      {
        std::cout << path1Name.data << "文件不存在!" << std::endl;
        flag = false;
      }
    }

    //找到file2
    switch(path2Type)
    {
    case msg.FILE_PATH:
      this->GotoFileRelativePosition(&cur2Position, workingPath, &path2Name, 2, &flag);
      break;
    case msg.FILE_WHOLE_PATH:
      this->GotoFileAbsolutePosition(&cur2Position, &path2Name, 2, &flag);
      break;
    default:
      std::cout << "待复制的路径名错误！" << std::endl;
      flag = false;
    }

    //获得文件对象
    if(flag)
    {
      file2 = (VirtualFile*)cur2Position->Find(path2Name);
      if(file2 == NULL)
      {
        std::cout << path2Name.data << "文件不存在!" << std::endl;
        flag = false;
      }
    }

    //将file1复制给file2
    if(flag)
    {
      file2->Copy(file1);
      std::cout << "已成功将" << file1->GetDirName().data << "复制到" << file2->GetDirName().data << "文件中" << std::endl;
    }
  }

  return flag;
}

//复制cur1Position下的所有文件到cur2Position下,并判断cur2Position中是否存在该名称的文件，存在，则询问是否覆盖，否则，直接复制
void CopyCmd::CopyAllFile(DirObject* cur1Position, DirObject** cur2Position, bool* flag)
{
  DirObject* tempPath1;
  DirObject* tempPath2;

  VirtualFile* file1 = NULL;
  VirtualFile* file2 = NULL;
  
  //遍历cur1Position的所有文件
  cur1Position->childrenLink.InitList();
  while(cur1Position->childrenLink.GetCurNode() != NULL)
  {
    tempPath1 = cur1Position->childrenLink.GetCurNode();
    if(tempPath1->GetTypeFlag() == 1)
    {
      bool isExist = false;
      file1 = (VirtualFile*)tempPath1;

      (*cur2Position)->childrenLink.InitList();
      if((*cur2Position)->Find(tempPath1->GetDirName()) != NULL)
      {
        tempPath2 = (*cur2Position)->childrenLink.GetCurNode();
        isExist = true;
      }

      //若文件不存在，直接复制文件
      if(!isExist)
      {
        file2 = new VirtualFile(tempPath1->GetDirName());
        file2->Copy((VirtualFile*)tempPath1);
        (*cur2Position)->AddDirNode(file2);
        std::cout << tempPath1->GetDirName().data << "已成功复制！" << std::endl;
      } 
      else//若文件存在，询问是否覆盖
      {
        std::cout << "文件已经存在，是否将其覆盖(y/n):";
        while(1)
        {
          char copyCmd;
          std::cin >> copyCmd;
          if(copyCmd == 'y' || copyCmd == 'Y')
          {
            file2 = (VirtualFile*)(*cur2Position)->Find(tempPath1->GetDirName());
            file2->Copy(file1);
            std::cout << "文件已覆盖！" << std::endl;
            break;
          }
          else if(copyCmd == 'n' || copyCmd == 'N')
          {
            std::cout << "文件未覆盖！" << std::endl;
            break;
          }
          std::cout <<"请确定是否覆盖文件：y为确定，n为取消" << std::endl;
        }
      }
    }
    cur1Position->childrenLink.GetNextNode();
  }  
}
//定位到指定文件夹
void CopyCmd::GotoAbsoluteFoldPosition(DirObject** curPosition, int pathID, bool* flag)
{
  MyString tempDirName;

  if(pathID == 1)
  {
    path1ElesList.InitList();

    while(path1ElesList.GetNextNode() != NULL)
    {
      tempDirName = path1ElesList.GetCurNode()->GetDirName();
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
  else if(pathID == 2)
  {
    path2ElesList.InitList();

    while(path2ElesList.GetNextNode() != NULL)
    {
      tempDirName = path2ElesList.GetCurNode()->GetDirName();
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
}
void CopyCmd::GotoRelativeFoldPosition(DirObject** curPosition, MyList<DirObject>* workingPath, int pathID, bool* flag)
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

  if(pathID == 1)
  {
    //遍历path1ElesList,找到指定位置，没有找到，返回false
    if((*flag))
    {
      path1ElesList.InitList();
      while(path1ElesList.GetCurNode() != NULL)
      {
        tempDirName = path1ElesList.GetCurNode()->GetDirName();
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
        path1ElesList.GetNextNode();
      }
    }
  }
  else if(pathID == 2)
  {
    //遍历path2ElesList,找到指定位置，没有找到，返回false
    if((*flag))
    {
      path2ElesList.InitList();
      while(path2ElesList.GetCurNode() != NULL)
      {
        tempDirName = path2ElesList.GetCurNode()->GetDirName();
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
        path2ElesList.GetNextNode();
      }
    }
  }
}

//文件的相对路径定位
void CopyCmd::GotoFileRelativePosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* copyDirName, int pathID, bool* flag)
{
  DirObject* dirNodePar  = NULL;      //临时Parent对象
  
  workingPath->InitList();
  dirNodePar = workingPath->GetCurNode();
  while(workingPath->GetNextNode() != NULL)
  {
    (*copyDirName) = workingPath->GetCurNode()->GetDirName();
    dirNodePar = (*curPosition);
    if((*curPosition)->Find((*copyDirName))!=NULL)
    {
      //查找下一目录
      (*curPosition) = (*curPosition)->Find((*copyDirName));
    }
    else
    {
      (*flag) = false;
      break;
    }
  }

  
  if(pathID == 1)
  {
    this->path1ElesList.InitList();
    if(this->path1ElesList.GetCurNode() == NULL)//若path1ElesList为空，则是workingPath的倒数第二层目录
    {
      (*flag) = false;
    }
    else if(this->path1ElesList.GetNextNode() == NULL)//如果path1ElesList只有一个元素，则为workingPath目录
    {
      //获得包含file1的文件夹名
      this->path1ElesList.InitList();
      (*copyDirName) = this->path1ElesList.GetCurNode()->GetDirName();  
    }
    else//若path1ElesList有两个以上元素，则为workingPath目录
    {
      DirObject* dirNodePar  = NULL;      //临时Parent对象

      //遍历path1ElesList，定位到对应路径
      path1ElesList.InitList();
      while(path1ElesList.GetCurNode() != NULL)
      {
        (*copyDirName) = path1ElesList.GetCurNode()->GetDirName();
        dirNodePar = (*curPosition);
        if((*curPosition)->Find((*copyDirName))!=NULL)
        {
          //查找下一目录
          (*curPosition) = (*curPosition)->Find((*copyDirName));
        }
        else
        {
          (*flag) = false;
          break;
        }
        path1ElesList.GetNextNode();
      }
      //返回到上一目录
      (*curPosition) = dirNodePar; 
    }
  }
  else if(pathID == 2)
  {
    this->path2ElesList.InitList();

    if(this->path2ElesList.GetCurNode() == NULL)//若path2ElesList为空，则是workingPath的倒数第二层目录
    {
      (*flag) = false;
    }
    else if(this->path2ElesList.GetNextNode() == NULL)//如果path2ElesList只有一个元素，则为workingPath目录
    {
      //获得包含file2的文件夹名
      this->path2ElesList.InitList();
      (*copyDirName) = this->path2ElesList.GetCurNode()->GetDirName();  
    }
    else//若path2ElesList有两个以上元素，则为workingPath目录
    {
      DirObject* dirNodePar  = NULL;      //临时Parent对象

      //遍历path2ElesList，定位到对应路径
      path2ElesList.InitList();
      while(path2ElesList.GetCurNode() != NULL)
      {
        (*copyDirName) = path2ElesList.GetCurNode()->GetDirName();
        dirNodePar = (*curPosition);
        if((*curPosition)->Find((*copyDirName))!=NULL)
        {
          //查找下一目录
          (*curPosition) = (*curPosition)->Find((*copyDirName));
        }
        else
        {
          (*flag) = false;
          break;
        }
        path2ElesList.GetNextNode();
      }
      //返回到上一目录
      (*curPosition) = dirNodePar; 
    }
  }

}

//文件的绝对路径定位
void CopyCmd::GotoFileAbsolutePosition(DirObject** curPosition, MyString* copyDirName, int pathID, bool* flag)
{
  //pathElesList的倒数第二层目录

  DirObject* dirNodePar  = NULL;      //临时Parent对象
  if(pathID == 1)
  {
    //遍历path1ElesList，定位到对应路径
    path1ElesList.InitList();
    dirNodePar = path1ElesList.GetCurNode();
    while(path1ElesList.GetNextNode() != NULL)
    {
      (*copyDirName) = path1ElesList.GetCurNode()->GetDirName();
      dirNodePar = (*curPosition);
      if((*curPosition)->Find((*copyDirName))!=NULL)
      {
        //查找下一目录
        (*curPosition) = (*curPosition)->Find((*copyDirName));
      }
      else
      {
        (*flag) = false;
        break;
      }

    }
  }
  else if(pathID == 2)
  {
    //遍历pathElesList，定位到对应路径
    path2ElesList.InitList();
    dirNodePar = path2ElesList.GetCurNode();
    while(path2ElesList.GetNextNode() != NULL)
    {
      (*copyDirName) = path2ElesList.GetCurNode()->GetDirName();
      dirNodePar = (*curPosition);
      if((*curPosition)->Find((*copyDirName))!=NULL)
      {
        //查找下一目录
        (*curPosition) = (*curPosition)->Find((*copyDirName));
      }
      else
      {
        (*flag) = false;
        break;
      }

    }
  }
  //返回到上一目录
  (*curPosition) = dirNodePar;
} 

void CopyCmd::SetPath1Type(int path1Type)
{
  this->path1Type = path1Type;
}

int CopyCmd::GetPath1Type()
{
  return path1Type;
}

void CopyCmd::SetPath2Type(int path2Type)
{
  this->path2Type = path2Type;
}

int CopyCmd::GetPath2Type()
{
  return path2Type;
}