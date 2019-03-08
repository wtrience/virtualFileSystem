
#include "VirtualFold.h"

VirtualFold::VirtualFold()
{

}

VirtualFold::VirtualFold(MyString name)
{
  this->dirName = name;
}

DirObject* VirtualFold::GetPreLink()
{
  return preLink;
}

void VirtualFold::SetPreLink(DirObject* preLink)
{
  this->preLink = preLink;
} 