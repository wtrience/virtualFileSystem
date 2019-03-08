
#include "DelCmd.h"

bool DelCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;                   //��¼�����Ƿ�ִ�гɹ�
  MyString tempDirName;               //Ŀ¼����
  DirObject* curPosition = rootDir;   //��¼��ǰλ��
  DirObject* dirNode = NULL;          //��ʱ����DirObject����
  int delFileNum;

  //����·������
  int pathType = this->GetPath1Type();
  switch(pathType)
  {
  case msg.FILE_PATH://ɾ�����·����ָ�����ļ�
    //��λ����ɾ���ļ���Ӧ���ļ���
    this->GotoRelativePreFlodPosition(&curPosition, workingPath, &tempDirName, &flag);

    //ɾ���ļ�
    if(flag)
    {
      dirNode = curPosition->Find(tempDirName);
      if(dirNode == NULL)
      {
        std::cout<< "�ļ������ڣ��޷�ɾ����" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        curPosition->childrenLink.DelNode(*dirNode);
        std::cout << "�ļ���ɾ����" << std::endl;
      }
    }
    else
    {
      std::cout << "�ļ������ڣ��޷�ɾ����" << std::endl;
    }
    break;
  case msg.FILE_WHOLE_PATH:
    //��λ����ɾ���ļ���Ӧ���ļ���
    GotoAbsolutePreFlodPosition(&curPosition, &tempDirName, &flag);

    //ɾ���ļ�
    if(flag)
    {
      dirNode = curPosition->Find(tempDirName);
      if(dirNode == NULL)
      {
        std::cout<< "�ļ������ڣ��޷�ɾ����" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        curPosition->childrenLink.DelNode(*dirNode);
        std::cout << "�ļ���ɾ����" << std::endl;
      }
    }
    else
    {
      std::cout << "�ļ������ڣ��޷�ɾ����" << std::endl;
    }
    break;
  case msg.FLOD_PATH:
    //���·������λ����Ӧ���ļ���
    GotoRelativeFoldPosition(&curPosition, workingPath, &flag);

    if(flag)
    {
      //ɾ���ļ����µ������ļ�
      DelAllFile(&curPosition, &flag);
      if(flag)
      {
        std::cout << "�ļ���ɾ����" << std::endl;
      }
      else
      {
        std::cout << "���ļ�����û���ļ���" << std::endl;
      }
    }
    else
    {
      std::cout << "·�������ڣ��޷�ɾ����" << std::endl;
    }
    break;
  case msg.FLOD_WHOLE_PATH:
    //����·������λ����Ӧ���ļ���
    this->GotoAbsoluteFoldPosition(&curPosition, &flag);
    
    if(flag)
    {
      //ɾ���ļ����µ������ļ�
      DelAllFile(&curPosition, &flag);
      if(flag)
      {
        std::cout << "�ļ���ɾ����" << std::endl;
      }
      else
      {
        std::cout << "���ļ�����û���ļ���" << std::endl;
      }
    }
    else
    {
      std::cout << "·�������ڣ��޷�ɾ����" << std::endl;
    }

    break;
  case msg.WILDCARD:
    
    this->pathElesList.InitList();
    if(this->pathElesList.GetCurNode() != NULL)
    {
      MyString dirName;
      //�ҵ���һĿ¼�ļ���
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &dirName, &flag);

      /*��ͨ���Ϊ�Ǻŵ�ʱ��ɾ����ǰ�ļ����µ������ļ�*/
      //MyString dirName = this->pathElesList.GetCurNode()->GetDirName();
      MyString star("*");

      if(star == dirName)
      {
        //ɾ����ǰ�ļ����µ������ļ�
        DelAllFile(&curPosition, &flag);
        std::cout << curPosition->GetDirName().data << "�������ļ���ɾ����" << std::endl;
      }
      /*��Ϊ�ʺŵ�ʱ�򣬱��������ļ������ļ���������бȶ�*/
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
              //ɾ��֮
              DirObject* dirNode = curPosition->Find(fileName);
              curPosition->childrenLink.DelNode(*dirNode);
              std::cout << fileName.data << "�ļ���ɾ����" << std::endl;
              delFileNum++;
            }
          }
          curPosition->childrenLink.GetNextNode();
        }

        if(delFileNum == 0)
        { 
          std::cout << "û���ҵ�ƥ����ļ���" << std::endl;
          flag = false;
          break;
        }
      }
    }
    else
    {
      std::cout << "·��Ϊ�գ������޷�ִ�У�" << std::endl;
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
          //ɾ��֮
          DirObject* dirNode = curPosition->Find(fileName);
          curPosition->childrenLink.DelNode(*dirNode);
          std::cout << fileName.data << "�ļ���ɾ����" << std::endl;
          delFileNum++;
        }
      }
      curPosition->childrenLink.GetNextNode();
    }

    if(delFileNum == 0)
    { 
      std::cout << "û���ҵ�ƥ����ļ���" << std::endl;
      flag = false;
      break;
    }
    break;
  default:
    std::cout << "�����ʽ����" << std::endl;
    flag = false;
  }

  return flag;
}

//��λ��ָ���ļ���
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

  //����workingPath,��λ����ǰĿ¼
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
  //����pathElesList,�ҵ�ָ��λ�ã�û���ҵ�������false
  if((*flag))
  {
    pathElesList.InitList();
    while(pathElesList.GetCurNode() != NULL)
    {
      tempDirName = pathElesList.GetCurNode()->GetDirName();
      if((*curPosition)->Find(tempDirName)!=NULL)
      {
        //������һĿ¼
        (*curPosition) = (*curPosition)->Find(tempDirName);
      }
      else
      {
        //·��������
        (*flag) = false;
        break;
      }
      pathElesList.GetNextNode();
    }
  }
}

//�ļ������·����λ
void DelCmd::GotoRelativePreFlodPosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* delDirName, bool* flag)
{
  DirObject* dirNodePar  = NULL;      //��ʱParent����
  
  workingPath->InitList();
  dirNodePar = workingPath->GetCurNode();
  while(workingPath->GetNextNode() != NULL)
  {
    (*delDirName) = workingPath->GetCurNode()->GetDirName();
    dirNodePar = (*curPosition);
    if((*curPosition)->Find((*delDirName))!=NULL)
    {
      //������һĿ¼
      (*curPosition) = (*curPosition)->Find((*delDirName));
    }
    else
    {
      (*flag) = false;
      break;
    }
  }

  this->pathElesList.InitList();

  if(this->pathElesList.GetCurNode() == NULL)//��pathElesListΪ�գ�����workingPath�ĵ����ڶ���Ŀ¼
  {
    (*flag) = false;
  }
  else if(this->pathElesList.GetNextNode() == NULL)//���pathElesListֻ��һ��Ԫ�أ���ΪworkingPathĿ¼
  {
    //��ô�ɾ���ļ��е��ļ�����
    this->pathElesList.InitList();
    (*delDirName) = this->pathElesList.GetCurNode()->GetDirName();  
  }
  else//��pathElesList����������Ԫ�أ���ΪworkingPathĿ¼
  {
    DirObject* dirNodePar  = NULL;      //��ʱParent����

    //����pathElesList����λ����Ӧ·��
    pathElesList.InitList();
    while(pathElesList.GetCurNode() != NULL)
    {
      (*delDirName) = pathElesList.GetCurNode()->GetDirName();
      dirNodePar = (*curPosition);
      if((*curPosition)->Find((*delDirName))!=NULL)
      {
        //������һĿ¼
        (*curPosition) = (*curPosition)->Find((*delDirName));
      }
      else
      {
        (*flag) = false;
        break;
      }
      pathElesList.GetNextNode();
    }
    //���ص���һĿ¼
    (*curPosition) = dirNodePar; 
  }
}

//�ļ��ľ���·����λ
void DelCmd::GotoAbsolutePreFlodPosition(DirObject** curPosition, MyString* delDirName, bool* flag)
{
  //pathElesList�ĵ����ڶ���Ŀ¼

  DirObject* dirNodePar  = NULL;      //��ʱParent����

  //����pathElesList����λ����Ӧ·��
  pathElesList.InitList();
  dirNodePar = pathElesList.GetCurNode();
  while(pathElesList.GetNextNode() != NULL)
  {
    (*delDirName) = pathElesList.GetCurNode()->GetDirName();
    dirNodePar = (*curPosition);
    if((*curPosition)->Find((*delDirName))!=NULL)
    {
      //������һĿ¼
      (*curPosition) = (*curPosition)->Find((*delDirName));
    }
    else
    {
      (*flag) = false;
      break;
    }

  }
  //���ص���һĿ¼
  (*curPosition) = dirNodePar;
} 

//ɾ���ļ����µ������ļ�
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