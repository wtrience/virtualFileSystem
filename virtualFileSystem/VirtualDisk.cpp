
#include "VirtualDisk.h"
#include "DirObject.h"
#include "VirtualFold.h"
#include "VirtualFile.h"
#include "MyString.h"
#include "MyList.h"

#include<string>
using namespace std;


VirtualDisk::VirtualDisk()
{
  
}

void VirtualDisk::InitFileSys()
{
  //����һ���ļ�ϵͳ������һЩ�ļ����ļ��У�

  //���ȣ�����C:��
  MyString volumeName("H:");
  rootDir = new DirObject(volumeName);
  rootDir->SetTypeFlag(2);//2Ϊ�̷�
  
  workingPath.AddNode(*rootDir); // ���ó�ʼ����·��ΪC:
  
  /*����test1�ļ���*/
  MyString test1Name = "test1";
  DirObject* test1 = new VirtualFold(test1Name);
  rootDir->AddDirNode(test1);

  //����test1�µ�test11�ļ���
  test1 = rootDir->Find(test1Name);   //���test1����
  MyString test11Name = "test11";
  DirObject* test11 = new VirtualFold(test11Name);
  test1->AddDirNode(test11);

  //����test1�µ�test12�ļ���
  MyString test12Name = "test12";
  DirObject* test12 = new VirtualFold(test12Name);
  test1->AddDirNode(test12);

  //����test1�µ�testfile11.txt
  MyString testfile11Name = "testfile11.txt";
  VirtualFile* testfile11 = new VirtualFile(testfile11Name);
  test1->AddDirNode((VirtualFile*)testfile11);

  //����test1�µ�testfile12.txt
  MyString testfile12Name = "testfile12.txt";
  VirtualFile* testfile12 = new VirtualFile(testfile12Name);
  test1->AddDirNode((VirtualFile*)testfile12);

    /*����test2�ļ���*/
  MyString test2Name = "test2";
  DirObject* test2 = new VirtualFold(test2Name);
  rootDir->AddDirNode(test2);

  //����test2�µ�test21�ļ���
  test2 = rootDir->Find(test2Name);   //���test2����
  MyString test21Name = "test21";
  DirObject* test21 = new VirtualFold(test21Name);
  test2->AddDirNode(test21);
}

void VirtualDisk::CmdExecute(MyString cmd)
{
	cmd_str = cmd;
  cmdFactory = new CmdFactory(cmd);
  cmd_object = cmdFactory->CreateCmd();
  if(cmd_object != NULL)
  {
    cmd_object->Execute(rootDir, &workingPath);
  }
}

MyString VirtualDisk::GetWorkingPath()
{
  MyString* workingPathStr = new MyString();
  int workingPathStrIndex = 0;

  workingPath.InitList();
  DirObject* dirNode = workingPath.GetCurNode();
  for(int i=0; dirNode->GetDirName().data[i] != '\0'; i++)
    workingPathStr->data[workingPathStrIndex++] = dirNode->GetDirName().data[i];
  workingPathStr->data[workingPathStrIndex++] = '\\';

  while(workingPath.GetNextNode() != NULL)
  {
    dirNode = workingPath.GetCurNode();
    for(int i=0; dirNode->GetDirName().data[i] != '\0'; i++)
      workingPathStr->data[workingPathStrIndex++] = dirNode->GetDirName().data[i];
    workingPathStr->data[workingPathStrIndex++] = '\\';
  }
  return *workingPathStr;
}

void VirtualDisk::SetWorkingPath(MyList<DirObject>* workingPath)
{
    //ʵ��֮
}
