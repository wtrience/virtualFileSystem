#pragma once 

class Msg
{
public:
  Msg();

public:
  //��������
  static enum cmdIDMsg{
    MKDIRCMD = 1,     //mkdir
    CDCMD = 2,        //cd
    COPYCMD = 3,      //copy
    DELCMD = 4,       //del
    RMDIRCMD = 5,     //rmdir
    DIRCMD = 6,       //dir
    COMPARECMD = 7,   //compare
    CREATENEWCMD = 8, //createNew
    EXITCMD = 9       //exit
  };

  const char* MKDIR;
  const char* CD;
  const char* COPY;
  const char* DEL;
  const char* RMDIR;
  const char* DIR;
  const char* COMPARE;
  const char* CREATENEW;
  const char* EXIT;

  //����Ԫ������
  static enum elementsTypeMsg{
      CMD_NAME = 1,   //������
      CMD_PARA = 2,   //�������
      CMD_PATH = 3    //����·��
    };
  //��������
  const char* QUOTATION_DONOT_MATCH;
  const char* PATH_IS_ALREADY_EXIST;
  const char* PATHNAME_IS_ILLEGAL;
  const char* CMDFORMAT_IS_ILLEGAL;
  const char* PATH_ISNOT_EXIST;
  const char* FILE_DOESNOT_EXIST;
  const char* FILE_IS_ALREADY_EXIST;

  static enum pathTypeMsg{
    FLOD_PATH = 0,              //�ļ��е����·��
    FLOD_WHOLE_PATH = 1,        //�ļ��еľ���·��
    FILE_PATH = 2,              //�ļ������·��
    FILE_WHOLE_PATH = 3,        //�ļ��ľ���·��
    WILDCARD = 4,               //ͨ��������·��
    BACK_TO_PARENT = 5,         //���ص���һĿ¼
    BACK_TO_ROOT = 6,           //���ص���Ŀ¼
    WILDCARD_WHOLE = 7          //ͨ����ľ���·��
  };
};