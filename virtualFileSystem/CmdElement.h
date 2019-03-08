#pragma once 
#include "MyString.h"

class CmdElement : public MyString
{
private:
  int elementType;

public:
  CmdElement();
  CmdElement(char cmdElement[]);
  CmdElement operator = (CmdElement source);
  bool operator == (CmdElement value);
  void SetElementsType(int type);
  int GetElementsType();
  
};