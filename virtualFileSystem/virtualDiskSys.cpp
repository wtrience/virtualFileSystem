// virtualDiskSys.cpp : 定义控制台应用程序的入口点。
#include <iostream>
#include "VirtualDisk.h"

using namespace std;

int main(int argc, char* argv[])
{ 
	VirtualDisk virtualDisk;
  //首先初始化磁盘
  virtualDisk.InitFileSys();

  //等待用户输入命令
  char cmd[100];
  bool flag = true;

  while(1)
  {
    if(flag)
    {
      MyString workingPath = virtualDisk.GetWorkingPath();
      cout << workingPath.data << ":";
      flag = false;
    }
    cin.getline(cmd, 100);          //获得用户输入的命令

    if(cmd[0] != '\0')
    {
		virtualDisk.CmdExecute(cmd);    //执行用户命令
		cout << endl;

      for(int i=0; i<100; i++)
        cmd[i] = '\0';

      flag = true;
    }
  }

  system("pause");

  return 0;
}