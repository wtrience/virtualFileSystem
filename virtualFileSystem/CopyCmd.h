#pragma once 
#include "MyList.h"
#include "DirObject.h"
#include "Cmd.h"

class CopyCmd : public Cmd
{
public:
  MyList<DirObject> path2ElesList;
  MyList<DirObject> path1ElesList;

private:
  int path1Type;
  int path2Type;

public:
  bool Execute(DirObject* rootDir, MyList<DirObject>* workingPath);
  void SetPath1Type(int path1Type);
  int GetPath1Type();
  void SetPath2Type(int path2Type);
  int GetPath2Type();

private:
  //�ļ������·����λ
  void GotoFileRelativePosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* copyDirName, int pathID, bool* flag);
  //�ļ��ľ���·����λ
  void GotoFileAbsolutePosition(DirObject** curPosition, MyString* copyDirName, int pathID, bool* flag);

  //��λ��ָ���ļ���
  void GotoAbsoluteFoldPosition(DirObject** curPosition, int pathID, bool* flag);
  void GotoRelativeFoldPosition(DirObject** curPosition, MyList<DirObject>* workingPath, int pathID, bool* flag);

  //�����ļ����µ������ļ�
  void CopyAllFile(DirObject* cur1Position, DirObject** cur2Position, bool* flag);
};