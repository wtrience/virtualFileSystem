#pragma once 
#include "DirObject.h"
#include "MyString.h"

class VirtualFile : public DirObject
{
public:
  int size;
  MyString type;
  

private:
  int curPosition;
  int endOfFile;

public:
  VirtualFile();
  VirtualFile(MyString name);
  void BackToFileHead();
  char* Read();
  void Write(char* content);
  void Copy(VirtualFile* file);
  void Append(char* content);
  bool Compare(VirtualFile* file);

  VirtualFile operator =(VirtualFile value);
  bool operator ==(VirtualFile value);

  void SetFileName(MyString name);
  MyString GetFileName();
  void SetFileType(MyString type);
  MyString GetFileType();
};