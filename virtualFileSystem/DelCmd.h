#pragma once 
#include "MyList.h"
#include "DirObject.h"
#include "Cmd.h"

class DelCmd : public Cmd
{
public:
  MyList<DirObject> pathElesList;

private:
  int path1Type;

public:
  bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
  void SetPath1Type(int path1Type);
  int GetPath1Type();

private:
  //�������ļ����ļ��в���
  void GotoAbsolutePreFlodPosition(DirObject** curPosition, MyString* delDirName, bool* flag);
  void GotoRelativePreFlodPosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* delDirName, bool* flag);

  //��λ��ָ���ļ���
  void GotoAbsoluteFoldPosition(DirObject** curPosition, bool* flag);
  void GotoRelativeFoldPosition(DirObject** curPosition, MyList<DirObject>* workingPath, bool* flag);

  void DelAllFile(DirObject** curPosition, bool* flag);
};