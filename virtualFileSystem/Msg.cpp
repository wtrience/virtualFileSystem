
#include "Msg.h"

Msg::Msg()
{
  QUOTATION_DONOT_MATCH = "引号不匹配";
  PATH_IS_ALREADY_EXIST = "目录已经存在";
  PATHNAME_IS_ILLEGAL = "路径名非法";
  CMDFORMAT_IS_ILLEGAL = "命令格式非法";
  PATH_ISNOT_EXIST = "路径不存在";
  FILE_DOESNOT_EXIST = "文件不存在";
  FILE_IS_ALREADY_EXIST = "文件已经存在";

  MKDIR = "mkdir";
  CD = "cd";
  COPY = "copy";
  DEL = "del";
  RMDIR = "rmdir";
  DIR = "dir";
  COMPARE = "compare";
  EXIT = "exit";
}