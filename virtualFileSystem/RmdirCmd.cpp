
#include "RmdirCmd.h"

RmdirCmd::RmdirCmd()
{
  for(int i=0; i<PARASIZE; i++)
    para[i] = '\0';
}

bool RmdirCmd::Execute(DirObject* rootDir, MyList<DirObject>* workingPath)
{
  bool flag = true;                   //��¼�����Ƿ�ִ�гɹ�
  MyString delDirName;               //Ŀ¼����
  DirObject* curPosition = rootDir;   //��¼��ǰλ��
  DirObject* dirNode = NULL;          //��ʱ����DirObject����

  //������������
  int paraType = -1;
  if(para[0] == '\0')//����Ϊ��ʱ��paraTypeΪ0
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
  case 0://�޲���
    //�ҵ����ļ��е���һ��Ŀ¼��ַ
    if(this->path1Type == 0)//���Ŀ¼
    {
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &delDirName, &flag);
    }
    else if(this->path1Type == 1)//����·��
    {
      this->GotoAbsolutePreFlodPosition(&curPosition, &delDirName, &flag);
    }
    //�鿴���ļ����Ƿ�Ϊ�գ��ǣ�ɾ��������ʾ�ļ��в�Ϊ�գ��޷�ɾ��
    if(flag)
    {
      dirNode = curPosition->Find(delDirName);
      if(dirNode == NULL)
      {
        std::cout<< "�ļ��в����ڣ��޷�ɾ����" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        if(dirNode->childrenLink.GetCurNode() == NULL)
        {
          curPosition->childrenLink.DelNode(*dirNode);
          std::cout << "�ļ�����ɾ����" << std::endl;
        }
        else
        {
          flag = false;
          std::cout << "�ļ��зǿգ��޷�ɾ���ļ��У�"<< std::endl;
        }
      }
    }
    else
    {
      std::cout << "�ļ��в����ڣ�ɾ��ʧ��!" << std::endl;
    }
    break;
  case 1://����Ϊ/s������ָ��ɾ�������ļ���
    //�ҵ����ļ��е���һ��Ŀ¼��ַ
    if(this->path1Type == 0)//���Ŀ¼
    {
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &delDirName, &flag);
    }
    else if(this->path1Type == 1)//����·��
    {
      this->GotoAbsolutePreFlodPosition(&curPosition, &delDirName, &flag);
    }
    //�鿴���ļ����Ƿ�Ϊ�գ��ǣ�ɾ������ѯ���û��Ƿ�ɾ��
    if(flag)
    {
      dirNode = curPosition->Find(delDirName);
      if(dirNode == NULL)
      {
        std::cout<< "�ļ��в����ڣ��޷�ɾ����" << std::endl;
        flag = false;
      }
      else
      {
        dirNode->childrenLink.InitList();
        if(dirNode->childrenLink.GetCurNode() == NULL)
        {
          curPosition->childrenLink.DelNode(*dirNode);
          std::cout << "�ļ�����ɾ����" << std::endl;
        }
        else
        {
          std::cout << "�ļ��зǿգ�ȷ��Ҫɾ���ļ��У�y/n��:";
          while(1)
          {
            char delCmd;
            std::cin >> delCmd;
            if(delCmd == 'y' || delCmd == 'Y')
            {
              curPosition->childrenLink.DelNode(*dirNode);
              std::cout << "�ļ�����ɾ����" << std::endl;
              break;
            }
            else if(delCmd == 'n' || delCmd == 'N')
            {
              std::cout << "�ļ���δɾ����" << std::endl;
              break;
            }
            std::cout <<"��ȷ���Ƿ�ɾ���ļ��У�yΪȷ����nΪȡ��" << std::endl;
          }
        }
      }
    }
    else
    {
      std::cout << "�ļ��в����ڣ�ɾ��ʧ�ܣ�" << std::endl;
    }
    break;
  case 2://����Ϊ/s/q������ָ���Բ�ѯ�ʵ�״̬ɾ�������ļ���
    //�ҵ����ļ��е���һ��Ŀ¼��ַ
    if(this->path1Type == 0)//���Ŀ¼
    {
      this->GotoRelativePreFlodPosition(&curPosition, workingPath, &delDirName, &flag);
    }
    else if(this->path1Type == 1)//����·��
    {
      this->GotoAbsolutePreFlodPosition(&curPosition, &delDirName, &flag);
    }
    //ɾ�������ļ���
    if(flag)
    {
      dirNode = curPosition->Find(delDirName);
      if(dirNode == NULL)
      {
        std::cout<< "�ļ��в����ڣ��޷�ɾ����" << std::endl;
        flag = false;
      }
      else
      {
        curPosition->childrenLink.DelNode(*dirNode);
        std::cout << "�ļ�����ɾ����" << std::endl;
      }
    }
    else
    {
      std::cout << "�ļ���ɾ��ʧ��!" << std::endl;
    }
    break;
  case -1:
  default:
    std::cout << "�������ʹ���\n" <<std::endl;
  }

  return false;
}

//���·����λ
void RmdirCmd::GotoRelativePreFlodPosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* delDirName, bool* flag)
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
    //pathElesList�ĵ����ڶ���Ŀ¼
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

//����·����λ
void RmdirCmd::GotoAbsolutePreFlodPosition(DirObject** curPosition, MyString* delDirName, bool* flag)
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

void RmdirCmd::SetPath1Type(int path1Type)
{
  this->path1Type = path1Type;
}

int RmdirCmd::GetPath1Type()
{
  return path1Type;
}