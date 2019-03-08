
#include "MyList.h"
#include "DirObject.h"

DirObject::DirObject()
{
  this->typeFlag = 0;
}

DirObject::DirObject(MyString dirName)
{
  DirObject();

  this->dirName = dirName;
  this->typeFlag = 0;
  for(int i=0; dirName.data[i] != '\0'; i++)
  {
    if(dirName.data[i] == '.')
    {
      this->typeFlag = 1;
      break;
    }
  }
  
}

DirObject* DirObject::Find(MyString name)
{
  TypeAnalysis();

  childrenLink.InitList();
  DirObject* result = childrenLink.GetCurNode();
  while(result != NULL)
  {
    if(result->dirName == name)
    {
      break;
    }
    else
    {
      result = childrenLink.GetNextNode();
    }
  }

  return result;
}

int DirObject::TypeAnalysis()
{
  //包含'.'的dirName当做文件处理，否则当做文件夹处理
  int typeFlag = 0;
  for(int i=0; dirName.data[i] != '\0'; i++)
  {
    if(dirName.data[i] == '.')
    {
      typeFlag = 1;
      break;
    }
  }
  this->typeFlag = typeFlag;

  return typeFlag;
}

//新建文件夹或者文件
bool DirObject::AddDirNode(DirObject* node)
{
  TypeAnalysis();

  bool flag = false;
  
  if(node != NULL)
  {
    childrenLink.AddNode(*node);
    node->TypeAnalysis();
    flag = true;
  }
  return flag;
}


MyString DirObject::GetDirName()
{
  return dirName;
}

void DirObject::SetDirName(MyString name)
{
  dirName = name;
}

int DirObject::GetTypeFlag()
{
  return typeFlag;
}

void DirObject::SetTypeFlag(int typeFlag)
{ 
  this->typeFlag = typeFlag;
}

DirObject DirObject::operator = (DirObject value)
{
  dirName = value.dirName;
  childrenLink = value.childrenLink;
  TypeAnalysis();
  if(typeFlag == 1)
  {
    for(int i=0; i<SIZE; i++)
      content[i] = value.content[i];
  }

  return (*this);
}

bool DirObject::operator ==(DirObject value)
{
  bool flag = false;

  if(value.dirName == dirName && value.typeFlag == typeFlag)// && childrenLink. == value.childrenLink)
  {
    flag = true;
  }

  return flag;
}