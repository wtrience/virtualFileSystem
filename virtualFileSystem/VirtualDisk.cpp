
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
  //创建一个文件系统（包含一些文件和文件夹）

  //首先，创建C:盘
  MyString volumeName("H:");
  rootDir = new DirObject(volumeName);
  rootDir->SetTypeFlag(2);//2为盘符
  
  workingPath.AddNode(*rootDir); // 设置初始工作路径为C:
  
  /*创建test1文件夹*/
  MyString test1Name = "test1";
  DirObject* test1 = new VirtualFold(test1Name);
  rootDir->AddDirNode(test1);

  //创建test1下的test11文件夹
  test1 = rootDir->Find(test1Name);   //获得test1对象
  MyString test11Name = "test11";
  DirObject* test11 = new VirtualFold(test11Name);
  test1->AddDirNode(test11);

  //创建test1下的test12文件夹
  MyString test12Name = "test12";
  DirObject* test12 = new VirtualFold(test12Name);
  test1->AddDirNode(test12);

  //创建test1下的testfile11.txt
  MyString testfile11Name = "testfile11.txt";
  VirtualFile* testfile11 = new VirtualFile(testfile11Name);
  test1->AddDirNode((VirtualFile*)testfile11);

  //创建test1下的testfile12.txt
  MyString testfile12Name = "testfile12.txt";
  VirtualFile* testfile12 = new VirtualFile(testfile12Name);
  test1->AddDirNode((VirtualFile*)testfile12);

    /*创建test2文件夹*/
  MyString test2Name = "test2";
  DirObject* test2 = new VirtualFold(test2Name);
  rootDir->AddDirNode(test2);

  //创建test2下的test21文件夹
  test2 = rootDir->Find(test2Name);   //获得test2对象
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
    //实现之
}
