// virtualDiskSys.cpp : �������̨Ӧ�ó������ڵ㡣
#include <iostream>
#include "VirtualDisk.h"

using namespace std;

int main(int argc, char* argv[])
{ 
	VirtualDisk virtualDisk;
  //���ȳ�ʼ������
  virtualDisk.InitFileSys();

  //�ȴ��û���������
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
    cin.getline(cmd, 100);          //����û����������

    if(cmd[0] != '\0')
    {
		virtualDisk.CmdExecute(cmd);    //ִ���û�����
		cout << endl;

      for(int i=0; i<100; i++)
        cmd[i] = '\0';

      flag = true;
    }
  }

  system("pause");

  return 0;
}