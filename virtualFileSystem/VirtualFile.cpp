#include "VirtualFile.h"

VirtualFile::VirtualFile()
{
  typeFlag = 1;
  for(int i=0; i<SIZE; i++)
    content[i] = '#';
}

VirtualFile::VirtualFile(MyString name)
{
  VirtualFile();

  dirName = name;
  curPosition = 0;
  endOfFile = 0;
  size = 0;
  
  int i;
  for(i=0; name.data[i] != '.'; i++);
  int j;
  for(i++,j=0; name.data[i] != '\0'; i++,j++)
  {
    type.data[j] = name.data[i];
  }
}

char* VirtualFile::Read()
{
  return content;
}

void VirtualFile::Write(char* content)
{

}


void VirtualFile::Copy(VirtualFile* file)
{
  curPosition = 0;
  endOfFile = 0;
  size = 0;

  for( endOfFile=0; file->content[endOfFile] != '#'; endOfFile++)
  {
    this->content[endOfFile] = file->content[endOfFile];
    size++;
  }

  for(int i=endOfFile; i < SIZE; i++)
  {
    this->content[i] = '#';
  }
  
}


void VirtualFile::Append(char* content)
{
  while((*content) != '#')
  {
    this->content[endOfFile++] = *(content++);
    size++;
  }
}

bool VirtualFile::Compare(VirtualFile* file)
{
  bool flag = true;

  for(int i=0; i<endOfFile; i++)
  {
    if(this->content[i] != file->content[i])
   {
      flag = false;
      break;
   }
  }

  return flag;
}

void VirtualFile::SetFileName(MyString name)
{
  dirName = name;
}

MyString VirtualFile::GetFileName()
{
  return dirName;
}

void VirtualFile::SetFileType(MyString type)
{
  this->type = type;
}

MyString VirtualFile::GetFileType()
{
  return type;
}

VirtualFile VirtualFile::operator =(VirtualFile value)
{
   dirName = value.dirName;
   typeFlag = value.typeFlag;

   type = value.type;
   for(int i=0; i<SIZE; i++)
   {
     content[i] = value.content[i];
   }
   return (*this);
}

bool VirtualFile::operator ==(VirtualFile value)
{
  bool flag = true;
  for(int i=0; i<SIZE; i++)
  {
    if(content[i]!= value.content[i])
    {
      flag = false;
      break;
    }
  }
  return flag;
}

void VirtualFile::BackToFileHead()
{
  curPosition = 0;
}