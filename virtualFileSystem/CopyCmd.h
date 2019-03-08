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
  //文件的相对路径定位
  void GotoFileRelativePosition(DirObject** curPosition, MyList<DirObject>* workingPath, MyString* copyDirName, int pathID, bool* flag);
  //文件的绝对路径定位
  void GotoFileAbsolutePosition(DirObject** curPosition, MyString* copyDirName, int pathID, bool* flag);

  //定位到指定文件夹
  void GotoAbsoluteFoldPosition(DirObject** curPosition, int pathID, bool* flag);
  void GotoRelativeFoldPosition(DirObject** curPosition, MyList<DirObject>* workingPath, int pathID, bool* flag);

  //复制文件夹下的所有文件
  void CopyAllFile(DirObject* cur1Position, DirObject** cur2Position, bool* flag);
};