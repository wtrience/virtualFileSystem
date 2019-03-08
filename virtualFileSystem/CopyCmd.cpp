
#include "CopyCmd.h"

bool CopyCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;
  MyString tempDirName;               //Ŀ¼����
  DirObject* curPosition = rootDir;   //��¼��ǰλ��
  DirObject* dirNode = NULL;          //��ʱ����DirObject����

  DirObject* cur1Position = rootDir;  //��¼path1��ǰλ��
  DirObject* cur2Position = rootDir;  //��¼path2��ǰλ��

  MyString path1Name;     //��¼path1������
  MyString path2Name;     //��¼path2������

  VirtualFile* file1;     //file1����
  VirtualFile* file2;     //file2����

  int path1Type = this->GetPath1Type();
  int path2Type = this->GetPath2Type();

  //���ļ��и��Ƹ��ļ�
  if((path1Type == msg.FLOD_PATH || path1Type == msg.FLOD_WHOLE_PATH) && (path2Type == msg.FILE_PATH || path2Type == msg.FILE_WHOLE_PATH))
  {
    std::cout << "�޷����ļ��и��Ƹ��ļ���" << std::endl;
    flag = false;
  }

  //���ļ��и��Ƹ��ļ���
  else if((path1Type == msg.FLOD_PATH || path1Type == msg.FLOD_WHOLE_PATH) && (path2Type == msg.FLOD_PATH || path2Type == msg.FLOD_WHOLE_PATH))
  {
    //��λ��path1ElesList��Ӧ��·��
    switch(path1Type)
    {
    case msg.FLOD_PATH:
      this->GotoRelativeFoldPosition(&cur1Position, workingPath, 1, &flag);
      break;
    case msg.FLOD_WHOLE_PATH:
      this->GotoAbsoluteFoldPosition(&cur1Position,1, &flag);
      break;
    default:
      std::cout << "�����Ƶ�·��������" << std::endl;
      flag = false;
    }

    //��λ��path2ElesList��Ӧ��·��
    switch(path2Type)
    {
    case msg.FLOD_PATH:
      this->GotoRelativeFoldPosition(&cur2Position, workingPath, 2, &flag);
      break;
    case msg.FLOD_WHOLE_PATH:
      this->GotoAbsoluteFoldPosition(&cur2Position, 2, &flag);
      break;
    default:
      std::cout << "�����Ƶ�·��������" << std::endl;
      flag = false;
    }

    //��path1�ļ����µ������ļ����Ƶ�path2�У����ж�path2���Ƿ���ڸ����Ƶ��ļ������ڣ���ѯ���Ƿ񸲸ǣ�����ֱ�Ӹ���
    CopyAllFile(cur1Position, &cur2Position, &flag);

  }

  //���ļ����Ƹ��ļ���
  else if((path1Type == msg.FILE_PATH || path1Type == msg.FILE_WHOLE_PATH) && (path2Type == msg.FLOD_PATH || path2Type == msg.FLOD_WHOLE_PATH))
  {
    //�ҵ�file1
    switch(path1Type)
    {
    case msg.FILE_PATH://���·��
      this->GotoFileRelativePosition(&cur1Position, workingPath, &path1Name, 1, &flag);
      break;
    case msg.FILE_WHOLE_PATH://����·��
      this->GotoFileAbsolutePosition(&cur1Position, &path1Name, 1, &flag);
      break;
    default:
      std::cout << "�����Ƶ�·��������" << std::endl;
      flag = false;
    }
    //����ļ�����
    if(flag)
    {
      file1 = (VirtualFile*)cur1Position->Find(path1Name);
      if(file1 == NULL)
      {
        std::cout << path1Name.data << "�ļ�������!" << std::endl;
        flag = false;
      }
    }
    //��λ��path2ElesList��Ӧ��·��
    switch(path2Type)
    {
    case msg.FLOD_PATH:
      this->GotoRelativeFoldPosition(&cur2Position, workingPath, 2, &flag);
      break;
    case msg.FLOD_WHOLE_PATH:
      this->GotoAbsoluteFoldPosition(&cur2Position, 2, &flag);
      break;
    default:
      std::cout << "�����Ƶ�·��������" << std::endl;
      flag = false;
    }

    //���ļ����Ƶ�path2�У����ж�path2���Ƿ���ڸ����Ƶ��ļ������ڣ���ѯ���Ƿ񸲸ǣ�����ֱ�Ӹ���
    if(flag)
    {
      if(cur2Position->Find(path1Name) == NULL)
      {
        VirtualFile* copyFile = new VirtualFile(path1Name);
        copyFile->Copy(file1);
        cur2Position->AddDirNode(copyFile);
        std::cout << "�ѳɹ���" << path1Name.data << "���Ƶ�" << cur2Position->GetDirName().data << "�ļ�����" << std::endl;
      }
      else
      {
        std::cout << "�ļ��Ѿ����ڣ��Ƿ��串��(y/n):";
        while(1)
        {
          char copyCmd;
          std::cin >> copyCmd;
          if(copyCmd == 'y' || copyCmd == 'Y')
          {
            file2 = (VirtualFile*)cur2Position->Find(path1Name);
            file2->Copy(file1);
            std::cout << "�ļ��Ѹ��ǣ�" << std::endl;
            break;
          }
          else if(copyCmd == 'n' || copyCmd == 'N')
          {
            std::cout << "�ļ�δ���ǣ�" << std::endl;
            break;
          }
          std::cout <<"��ȷ���Ƿ񸲸��ļ���yΪȷ����nΪȡ��" << std::endl;
        }
      }
    }

  }

  //���ļ����Ƹ��ļ�
  else if((path1Type == msg.FILE_PATH || path1Type == msg.FILE_WHOLE_PATH) && (path2Type == msg.FILE_PATH || path2Type == msg.FILE_WHOLE_PATH))
  {
    //�ҵ�file1
    switch(path1Type)
    {
    case msg.FILE_PATH:
      this->GotoFileRelativePosition(&cur1Position, workingPath, &path1Name, 1, &flag);
      break;
    case msg.FILE_WHOLE_PATH:
      this->GotoFileAbsolutePosition(&cur1Position, &path1Name, 1, &flag);
      break;
    default:
      std::cout << "�����Ƶ�·��������" << std::endl;
      flag = false;
    }

    //����ļ�����
    if(flag)
    {
      file1 = (VirtualFile*)cur1Position->Find(path1Name);
      if(file1 == NULL)
      {
        std::cout << path1Name.data << "�ļ�������!" << std::endl;
        flag = false;
      }
    }

    //�ҵ�file2
    switch(path2Type)
    {
    case msg.FILE_PATH:
      this->GotoFileRelativePosition(&cur2Position, workingPath, &path2Name, 2, &flag);
      break;
    case msg.FILE_WHOLE_PATH:
      this->GotoFileAbsolutePosition(&cur2Position, &path2Name, 2, &flag);
      break;
    default:
      std::cout << "�����Ƶ�·��������" << std::endl;
      flag = false;
    }

    //����ļ�����
    if(flag)
    {
      file2 = (VirtualFile*)cur2Position->Find(path2Name);
      if(file2 == NULL)
      {
        std::cout << path2Name.data << "�ļ�������!" << std::endl;
        flag = false;
      }
    }

    //��file1���Ƹ�file2
    if(flag)
    {
      file2->Copy(file1);
      std::cout << "�ѳɹ���" << file1->GetDirName().data << "���Ƶ�" << file2->GetDirName().data << "�ļ���" << std::endl;
    }
  }

  return flag;
}

//����cur1Position�µ������ļ���cur2Position��,���ж�cur2Position���Ƿ���ڸ����Ƶ��ļ������ڣ���ѯ���Ƿ񸲸ǣ�����ֱ�Ӹ���
void CopyCmd::CopyAllFile(DirObject* cur1Position, DirObject** cur2Position, bool* flag)
{
  DirObject* tempPath1;
  DirObject* tempPath2;

  VirtualFile* file1 = NULL;
  VirtualFile* file2 = NULL;
  
  //����cur1Position�������ļ�
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

      //���ļ������ڣ�ֱ�Ӹ����ļ�
      if(!isExist)
      {
        file2 = new VirtualFile(tempPath1->GetDirName());
        file2->Copy((VirtualFile*)tempPath1);
        (*cur2Position)->AddDirNode(file2);
        std::cout << tempPath1->GetDirName().data << "�ѳɹ����ƣ�" << std::endl;
      } 
      else//���ļ����ڣ�ѯ���Ƿ񸲸�
      {
        std::cout << "�ļ��Ѿ����ڣ��Ƿ��串��(y/n):";
        while(1)
        {
          char copyCmd;
          std::cin >> copyCmd;
          if(copyCmd == 'y' || copyCmd == 'Y')
          {
            file2 = (VirtualFile*)(*cur2Position)->Find(tempPath1->GetDirName());
            file2->Copy(file1);
            std::cout << "�ļ��Ѹ��ǣ�" << std::endl;
            break;
          }
          else if(copyCmd == 'n' || copyCmd == 'N')
          {
            std::cout << "�ļ�δ���ǣ�" << std::endl;
            break;
          }
          std::cout <<"��ȷ���Ƿ񸲸��ļ���yΪȷ����nΪȡ��" << std::endl;
        }
      }
    }
    cur1Position->childrenLink.GetNextNode();
  }  
}
//��λ��ָ���ļ���
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

  if(pathID == 1)
  {
    //����path1ElesList,�ҵ�ָ��λ�ã�û���ҵ�������false
    if((*flag))
    {
      path1ElesList.InitList();
      while(path1ElesList.GetCurNode() != NULL)
      {
        tempDirName = path1ElesList.GetCurNode()->GetDirName();
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
        path1ElesList.GetNextNode();
      }
    }
  }
  else if(pathID == 2)
  {
    //����path2ElesList,�ҵ�ָ��λ�ã�û���ҵ�������false
    if((*flag))
    {
      path2ElesList.InitList();
      while(path2ElesList.GetCurNode() != NULL)
      {
        tempDirName = path2ElesList.GetCurNode()->GetDirName();
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
        path2ElesList.GetNextNode();
      }
    }
  }
}

//�ļ������·����λ
void CopyCmd::GotoFileRelativePosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* copyDirName, int pathID, bool* flag)
{
  DirObject* dirNodePar  = NULL;      //��ʱParent����
  
  workingPath->InitList();
  dirNodePar = workingPath->GetCurNode();
  while(workingPath->GetNextNode() != NULL)
  {
    (*copyDirName) = workingPath->GetCurNode()->GetDirName();
    dirNodePar = (*curPosition);
    if((*curPosition)->Find((*copyDirName))!=NULL)
    {
      //������һĿ¼
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
    if(this->path1ElesList.GetCurNode() == NULL)//��path1ElesListΪ�գ�����workingPath�ĵ����ڶ���Ŀ¼
    {
      (*flag) = false;
    }
    else if(this->path1ElesList.GetNextNode() == NULL)//���path1ElesListֻ��һ��Ԫ�أ���ΪworkingPathĿ¼
    {
      //��ð���file1���ļ�����
      this->path1ElesList.InitList();
      (*copyDirName) = this->path1ElesList.GetCurNode()->GetDirName();  
    }
    else//��path1ElesList����������Ԫ�أ���ΪworkingPathĿ¼
    {
      DirObject* dirNodePar  = NULL;      //��ʱParent����

      //����path1ElesList����λ����Ӧ·��
      path1ElesList.InitList();
      while(path1ElesList.GetCurNode() != NULL)
      {
        (*copyDirName) = path1ElesList.GetCurNode()->GetDirName();
        dirNodePar = (*curPosition);
        if((*curPosition)->Find((*copyDirName))!=NULL)
        {
          //������һĿ¼
          (*curPosition) = (*curPosition)->Find((*copyDirName));
        }
        else
        {
          (*flag) = false;
          break;
        }
        path1ElesList.GetNextNode();
      }
      //���ص���һĿ¼
      (*curPosition) = dirNodePar; 
    }
  }
  else if(pathID == 2)
  {
    this->path2ElesList.InitList();

    if(this->path2ElesList.GetCurNode() == NULL)//��path2ElesListΪ�գ�����workingPath�ĵ����ڶ���Ŀ¼
    {
      (*flag) = false;
    }
    else if(this->path2ElesList.GetNextNode() == NULL)//���path2ElesListֻ��һ��Ԫ�أ���ΪworkingPathĿ¼
    {
      //��ð���file2���ļ�����
      this->path2ElesList.InitList();
      (*copyDirName) = this->path2ElesList.GetCurNode()->GetDirName();  
    }
    else//��path2ElesList����������Ԫ�أ���ΪworkingPathĿ¼
    {
      DirObject* dirNodePar  = NULL;      //��ʱParent����

      //����path2ElesList����λ����Ӧ·��
      path2ElesList.InitList();
      while(path2ElesList.GetCurNode() != NULL)
      {
        (*copyDirName) = path2ElesList.GetCurNode()->GetDirName();
        dirNodePar = (*curPosition);
        if((*curPosition)->Find((*copyDirName))!=NULL)
        {
          //������һĿ¼
          (*curPosition) = (*curPosition)->Find((*copyDirName));
        }
        else
        {
          (*flag) = false;
          break;
        }
        path2ElesList.GetNextNode();
      }
      //���ص���һĿ¼
      (*curPosition) = dirNodePar; 
    }
  }

}

//�ļ��ľ���·����λ
void CopyCmd::GotoFileAbsolutePosition(DirObject** curPosition, MyString* copyDirName, int pathID, bool* flag)
{
  //pathElesList�ĵ����ڶ���Ŀ¼

  DirObject* dirNodePar  = NULL;      //��ʱParent����
  if(pathID == 1)
  {
    //����path1ElesList����λ����Ӧ·��
    path1ElesList.InitList();
    dirNodePar = path1ElesList.GetCurNode();
    while(path1ElesList.GetNextNode() != NULL)
    {
      (*copyDirName) = path1ElesList.GetCurNode()->GetDirName();
      dirNodePar = (*curPosition);
      if((*curPosition)->Find((*copyDirName))!=NULL)
      {
        //������һĿ¼
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
    //����pathElesList����λ����Ӧ·��
    path2ElesList.InitList();
    dirNodePar = path2ElesList.GetCurNode();
    while(path2ElesList.GetNextNode() != NULL)
    {
      (*copyDirName) = path2ElesList.GetCurNode()->GetDirName();
      dirNodePar = (*curPosition);
      if((*curPosition)->Find((*copyDirName))!=NULL)
      {
        //������һĿ¼
        (*curPosition) = (*curPosition)->Find((*copyDirName));
      }
      else
      {
        (*flag) = false;
        break;
      }

    }
  }
  //���ص���һĿ¼
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