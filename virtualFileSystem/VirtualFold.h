#pragma once 
#include "DirObject.h"
#include "MyString.h"

class VirtualFold : public DirObject
{
private:
  DirObject* preLink;

public:
  VirtualFold();
  VirtualFold(MyString name);
  DirObject* GetPreLink();
  void SetPreLink(DirObject* preLink);
};