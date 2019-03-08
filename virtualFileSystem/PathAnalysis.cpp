
#include "PathAnalysis.h"
#include "MyString.h"
#include <iostream>


PathAnalysis::PathAnalysis()
{

}

PathAnalysis::PathAnalysis(MyList<CmdElement>* cmdElementList, Cmd* cmd)
{
  PathAnalysis();

  this->cmdElementList = cmdElementList;
  this->cmd = cmd;
}

bool PathAnalysis::Split()
{
  bool flag = true;
  int pathNum = 0; //用于计算一个命令中含有几个路径变量

  //分割路径
  int cmdType = cmd->GetCmdID();
  cmdElementList->InitList();
  CmdElement* tempElement;
  switch(cmdType)
  {
  case 1: //mkdir
    mkdir = (MkdirCmd*)cmd;
    pathNum = 0;
    while(cmdElementList->GetNextNode() != NULL)
    {
      tempElement = cmdElementList->GetCurNode();
      if(tempElement->GetElementsType() == msg.CMD_PATH)
      {
        //分割命令
        pathNum++;
        int elementIndex = 0;
        while(tempElement->data[elementIndex] != '\0')
        {
          MyString* dirNodeName = new MyString();
          int nodeNameIndex = 0;
          while(tempElement->data[elementIndex] != '\\' && tempElement->data[elementIndex] != '\0')
          {
            dirNodeName->data[nodeNameIndex++] = tempElement->data[elementIndex++];
          }
          DirObject* tempDirObject = new DirObject(*dirNodeName);
          mkdir->pathElesList.AddNode(*tempDirObject);
          elementIndex++;
          delete dirNodeName;
          delete tempDirObject;
        }
      }
      if(pathNum > 1)
      {
        flag = false;
        std::cout << "命令格式错误！" << std::endl;
        break;
      }
    }
    break;

  case 2://cd 
    cd = (CdCmd*)cmd;
    pathNum = 0;
    while(cmdElementList->GetNextNode() != NULL)
    {
      tempElement = cmdElementList->GetCurNode();
      if(tempElement->GetElementsType() == msg.CMD_PATH)
      {
        //分割命令
        int elementIndex = 0;
        pathNum++;
        while(tempElement->data[elementIndex] != '\0')
        {
          MyString* dirNodeName = new MyString();
          int nodeNameIndex = 0;
          while(tempElement->data[elementIndex] != '\\'&& tempElement->data[elementIndex] != '\0')
          {
            dirNodeName->data[nodeNameIndex++] = tempElement->data[elementIndex++];
          }
          DirObject* tempDirObject = new DirObject(*dirNodeName);
          cd->pathElesList.AddNode(*tempDirObject);
          elementIndex++;
          delete dirNodeName;
          delete tempDirObject;
        }
      }
      if(pathNum > 1)
      {
        flag = false;
        std::cout << "命令格式错误！" << std::endl;
        break;
      }
    }
    break;

  case 3://copy
    copy = (CopyCmd*)cmd;
    pathNum = 0;
    while(cmdElementList->GetNextNode() != NULL)
    {
      tempElement = cmdElementList->GetCurNode();
      if(tempElement->GetElementsType() == msg.CMD_PATH)
      {
        //分割命令
        int elementIndex = 0;
        pathNum++;
        if(pathNum == 1)
        {
          while(tempElement->data[elementIndex] != '\0')
          {
            MyString* dirNodeName = new MyString();
            int nodeNameIndex = 0;
            while(tempElement->data[elementIndex] != '\\'&& tempElement->data[elementIndex] != '\0')
            {
              dirNodeName->data[nodeNameIndex++] = tempElement->data[elementIndex++];
            }
            DirObject* tempDirObject = new DirObject(*dirNodeName);
            copy->path1ElesList.AddNode(*tempDirObject);
            elementIndex++;
            delete dirNodeName;
            delete tempDirObject;
          }
        }
        else if(pathNum == 2)
        {
          while(tempElement->data[elementIndex] != '\0')
          {
            MyString* dirNodeName = new MyString();
            int nodeNameIndex = 0;
            while(tempElement->data[elementIndex] != '\\'&& tempElement->data[elementIndex] != '\0')
            {
              dirNodeName->data[nodeNameIndex++] = tempElement->data[elementIndex++];
            }
            DirObject* tempDirObject = new DirObject(*dirNodeName);
            copy->path2ElesList.AddNode(*tempDirObject);
            elementIndex++;
            delete dirNodeName;
            delete tempDirObject;
          }
        }
        else
        {
          flag = false;
          std::cout << "命令格式错误！" << std::endl;
          break;
        }
      }
    }
    break;

  case 4://del
    del = (DelCmd*)cmd;
    pathNum = 0;
    while(cmdElementList->GetNextNode() != NULL)
    {
      tempElement = cmdElementList->GetCurNode();
      if(tempElement->GetElementsType() == msg.CMD_PATH)
      {
        //分割命令
        int elementIndex = 0;
        pathNum++;
        while(tempElement->data[elementIndex] != '\0')
        {
          MyString* dirNodeName = new MyString();
          int nodeNameIndex = 0;
          while(tempElement->data[elementIndex] != '\\'&& tempElement->data[elementIndex] != '\0')
          {
            dirNodeName->data[nodeNameIndex++] = tempElement->data[elementIndex++];
          }
          DirObject* tempDirObject = new DirObject(*dirNodeName);
          del->pathElesList.AddNode(*tempDirObject);
          elementIndex++;
          delete dirNodeName;
          delete tempDirObject;
        }
      }

      if(pathNum > 1)
      {
        flag = false;
        std::cout << "命令格式错误！" << std::endl;
        break;
      }
    }
    break;

  case 5://rmdir
    rmdir = (RmdirCmd*)cmd;
    pathNum = 0;
    while(cmdElementList->GetNextNode() != NULL)
    {
      tempElement = cmdElementList->GetCurNode();
      if(tempElement->GetElementsType() == msg.CMD_PATH)
      {
        //分割命令
        int elementIndex = 0;
        pathNum++;
        while(tempElement->data[elementIndex] != '\0')
        {
          MyString* dirNodeName = new MyString();
          int nodeNameIndex = 0;
          while(tempElement->data[elementIndex] != '\\'&& tempElement->data[elementIndex] != '\0')
          {
            dirNodeName->data[nodeNameIndex++] = tempElement->data[elementIndex++];
          }
          DirObject* tempDirObject = new DirObject(*dirNodeName);
          rmdir->pathElesList.AddNode(*tempDirObject);
          elementIndex++;
          delete dirNodeName;
          delete tempDirObject;
        }
      }

      if(pathNum > 1)
      {
        flag = false;
        std::cout << "命令格式错误！" << std::endl;
        break;
      }
    }
    break;

  case 6://dir
    dir = (DirCmd*)cmd;
    pathNum = 0;
    while(cmdElementList->GetNextNode() != NULL)
    {
      tempElement = cmdElementList->GetCurNode();
      if(tempElement->GetElementsType() == msg.CMD_PATH)
      {
        //分割命令
        int elementIndex = 0;
        pathNum++;
        while(tempElement->data[elementIndex] != '\0')
        {
          MyString* dirNodeName = new MyString();
          int nodeNameIndex = 0;
          while(tempElement->data[elementIndex] != '\\'&& tempElement->data[elementIndex] != '\0')
          {
            dirNodeName->data[nodeNameIndex++] = tempElement->data[elementIndex++];
          }
          DirObject* tempDirObject = new DirObject(*dirNodeName);
          dir->pathElesList.AddNode(*tempDirObject);
          elementIndex++;
          delete dirNodeName;
          delete tempDirObject;
        }
      }

      if(pathNum > 1)
      {
        flag = false;
        std::cout << "命令格式错误！" << std::endl;
        break;
      }
    }
    break;

  

  default:
    flag = false;
    std::cout <<"系统无法解析当前命令" << std::endl;
  }  

  return flag;
}

void PathAnalysis::PathTypeAnalysis()
{
  MyString tempRoot("C:");
  MyString tempBackToParent("..");
  MyString tempBackToRoot("/");
  MyString temp;

  int cmdType = cmd->GetCmdID();
  DirObject* tempDirNode;

  //创建命令,并进行初始化
  switch(cmdType)
  {
  case 1: //mkdir
    mkdir = (MkdirCmd*)cmd;
    mkdir->pathElesList.InitList();
    if(mkdir->pathElesList.GetCurNode() != NULL)
    {
      temp = mkdir->pathElesList.GetCurNode()->GetDirName();
    }
    else
    {
      temp = "";
    }
    if(temp == tempRoot)
    {
      mkdir->SetPath1Type(msg.FLOD_WHOLE_PATH);
    }
    else
    {
      mkdir->SetPath1Type(msg.FLOD_PATH);
    }
    break;

  case 2://cd 
    cd = (CdCmd*)cmd;
    cd->pathElesList.InitList();
    if(cd->pathElesList.GetCurNode() != NULL)
    {
      temp = cd->pathElesList.GetCurNode()->GetDirName();
    }
    else
    { 
      temp = "";
    }
    if(temp == tempBackToParent)
    {
      cd->SetPath1Type(msg.BACK_TO_PARENT);
    }
    else if(temp == tempBackToRoot)
    {
      cd->SetPath1Type(msg.BACK_TO_ROOT);
    }
    else if(temp == tempRoot)
    {
      cd->SetPath1Type(msg.FLOD_WHOLE_PATH);
    }
    else
    {
      cd->SetPath1Type(msg.FLOD_PATH);
    }
    break;

  case 3://copy
    copy = (CopyCmd*)cmd;
    /*判断路径1的类型*/
    copy->path1ElesList.InitList();
    tempDirNode = copy->path1ElesList.GetCurNode();
    if(tempDirNode != NULL)
    {
      temp = tempDirNode->GetDirName();
    }
    else
    {
      temp = "";
    }
    if(copy->path1ElesList.GetNextNode() == NULL)
    {
      bool isFile = false;
      int index = 0;
      while(tempDirNode->GetDirName().data[index] != '\0')
      {
        if(tempDirNode->GetDirName().data[index++] == '.')
        {
          isFile = true;
          break;
        }
      }

      if(isFile)
      {
        copy->SetPath1Type(msg.FILE_PATH);
      }
      else
      {
        copy->SetPath1Type(msg.FLOD_PATH);
      }
    }
    else
    {
      tempDirNode = copy->path1ElesList.GetCurNode();
      while(copy->path1ElesList.GetNextNode() != NULL)
      {
        tempDirNode = copy->path1ElesList.GetCurNode();
      }

      bool isFile = false;
      int index = 0;
      while(tempDirNode->GetDirName().data[index] != '\0')
      {
        if(tempDirNode->GetDirName().data[index++] == '.')
        {
          isFile = true;
          break;
        }
      }

      if(isFile && temp == tempRoot)
      {
        copy->SetPath1Type(msg.FILE_WHOLE_PATH);
      }
      else if(!isFile && temp == tempRoot)
      {
        copy->SetPath1Type(msg.FLOD_WHOLE_PATH);
      }
      else if(isFile)
      {
        copy->SetPath1Type(msg.FILE_PATH);
      }
      else if(!isFile)
      {
        copy->SetPath1Type(msg.FLOD_PATH);
      }
    }
    
    /*判断路径2的类型*/
    copy->path2ElesList.InitList();
    tempDirNode = copy->path2ElesList.GetCurNode();
    if(tempDirNode != NULL)
    {
      temp = tempDirNode->GetDirName();
    }
    else
    {
      temp = "";
    }
    if(copy->path2ElesList.GetNextNode() == NULL)
    {
      bool isFile = false;
      int index = 0;
      while(tempDirNode->GetDirName().data[index] != '\0')
      {
        if(tempDirNode->GetDirName().data[index++] == '.')
        {
          isFile = true;
          break;
        }
      }

      if(isFile)
      {
        copy->SetPath2Type(msg.FILE_PATH);
      }
      else
      {
        copy->SetPath2Type(msg.FLOD_PATH);
      }
    }
    else
    {
      tempDirNode = copy->path2ElesList.GetCurNode();
      while(copy->path2ElesList.GetNextNode() != NULL)
      {
        tempDirNode = copy->path2ElesList.GetCurNode();
      }

      bool isFile = false;
      int index = 0;
      while(tempDirNode->GetDirName().data[index] != '\0')
      {
        if(tempDirNode->GetDirName().data[index++] == '.')
        {
          isFile = true;
          break;
        }
      }

      if(isFile && temp == tempRoot)
      {
        copy->SetPath2Type(msg.FILE_WHOLE_PATH);
      }
      else if(!isFile && temp == tempRoot)
      {
        copy->SetPath2Type(msg.FLOD_WHOLE_PATH);
      }
      else if(isFile)
      {
        copy->SetPath2Type(msg.FILE_PATH);
      }
      else if(!isFile)
      {
        copy->SetPath2Type(msg.FLOD_PATH);
      }
    }
      
    break;

  case 4://del
    del = (DelCmd*)cmd;
    del->pathElesList.InitList();
    tempDirNode = del->pathElesList.GetCurNode();
    if(tempDirNode != NULL)
    {
      temp = tempDirNode->GetDirName();
    }
    else
    {
      temp = "";
    }

    if(temp == tempRoot)
    {
      tempDirNode = del->pathElesList.GetCurNode();
      while(del->pathElesList.GetNextNode() != NULL)
      {
        tempDirNode = del->pathElesList.GetCurNode();
      }

      bool isFile = false;
      bool isHaveWildCard = false;
      int index = 0;
      while(tempDirNode->GetDirName().data[index] != '\0')
      {
        if(tempDirNode->GetDirName().data[index] == '*' || tempDirNode->GetDirName().data[index] == '?')
        {
          isHaveWildCard = true;
          break;
        }
        if(tempDirNode->GetDirName().data[index] == '.')
        {
          isFile = true;
        }
        index++;
      }

      if(isHaveWildCard)
      {
        del->SetPath1Type(msg.WILDCARD_WHOLE);    //含有通配符的绝对路径
      }
      else
      {
        if(isFile)
        {
          del->SetPath1Type(msg.FILE_WHOLE_PATH);
        }
        else
        {
          del->SetPath1Type(msg.FLOD_WHOLE_PATH);
        }
      }
    }
    else
    {
      if(del->pathElesList.GetNextNode() == NULL)//path只有一个元素
      {
        int index = 0;
        bool isFile = false;
        bool isHaveWildCard = false;
        while(tempDirNode->GetDirName().data[index] != '\0')
        {
          if(tempDirNode->GetDirName().data[index] == '*' || tempDirNode->GetDirName().data[index] == '?')
          {
            isHaveWildCard = true;
            break;
          }
          if(tempDirNode->GetDirName().data[index] == '.')
          {
            isFile = true;
          }
          index++;
        }

        if(isHaveWildCard)
        {
          del->SetPath1Type(msg.WILDCARD);    //含有通配符
        }
        else
        {
          if(isFile)
          {
            del->SetPath1Type(msg.FILE_PATH);
          }
          else
          {
            del->SetPath1Type(msg.FLOD_PATH);
          }
        }
      }
      else//path有多个元素
      {
        tempDirNode = del->pathElesList.GetCurNode();
        while(del->pathElesList.GetNextNode() != NULL)
        {
          tempDirNode = del->pathElesList.GetCurNode();
        }

        bool isFile = false;
        bool isHaveWildCard = false;
        int index = 0;
        while(tempDirNode->GetDirName().data[index] != '\0')
        {
          if(tempDirNode->GetDirName().data[index] == '*' || tempDirNode->GetDirName().data[index] == '?')
          {
            isHaveWildCard = true;
            break;
          }
          if(tempDirNode->GetDirName().data[index] == '.')
          {
            isFile = true;
          }
          index++;
        }

        if(isHaveWildCard)
        {
          del->SetPath1Type(msg.WILDCARD);    //含有通配符
        }
        else
        {
          if(isFile)
          {
            del->SetPath1Type(msg.FILE_PATH);
          }
          else
          {
            del->SetPath1Type(msg.FLOD_PATH);
          }
        }
      }
    }
    
    break;

  case 5://rmdir
    rmdir = (RmdirCmd*)cmd;
    rmdir->pathElesList.InitList();
    if(rmdir->pathElesList.GetCurNode() != NULL)
    {
      temp = rmdir->pathElesList.GetCurNode()->GetDirName();
    }
    else
    { 
      temp = "";
    }
    if(temp == tempRoot)
    {
      rmdir->SetPath1Type(msg.FLOD_WHOLE_PATH);
    }
    else
    {
      rmdir->SetPath1Type(msg.FLOD_PATH);
    }
    break;

  case 6://dir
    dir = (DirCmd*)cmd;
    dir->pathElesList.InitList();
    if(dir->pathElesList.GetCurNode() != NULL)
    {
      temp = dir->pathElesList.GetCurNode()->GetDirName();
    }
    else
    {
      temp = "";
    }

    if(temp == tempRoot)
    {
      dir->SetPath1Type(msg.FLOD_WHOLE_PATH);
    }
    else
    {
      dir->SetPath1Type(msg.FLOD_PATH);
    }
    break;

  } 
}