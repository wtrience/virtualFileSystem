#pragma once 

class Msg
{
public:
  Msg();

public:
  //命令类型
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

  //命令元素类型
  static enum elementsTypeMsg{
      CMD_NAME = 1,   //命令名
      CMD_PARA = 2,   //命令参数
      CMD_PATH = 3    //命令路径
    };
  //错误类型
  const char* QUOTATION_DONOT_MATCH;
  const char* PATH_IS_ALREADY_EXIST;
  const char* PATHNAME_IS_ILLEGAL;
  const char* CMDFORMAT_IS_ILLEGAL;
  const char* PATH_ISNOT_EXIST;
  const char* FILE_DOESNOT_EXIST;
  const char* FILE_IS_ALREADY_EXIST;

  static enum pathTypeMsg{
    FLOD_PATH = 0,              //文件夹的相对路径
    FLOD_WHOLE_PATH = 1,        //文件夹的绝对路径
    FILE_PATH = 2,              //文件的相对路径
    FILE_WHOLE_PATH = 3,        //文件的绝对路径
    WILDCARD = 4,               //通配符的相对路径
    BACK_TO_PARENT = 5,         //返回到上一目录
    BACK_TO_ROOT = 6,           //返回到根目录
    WILDCARD_WHOLE = 7          //通配符的绝对路径
  };
};