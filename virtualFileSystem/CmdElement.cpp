#include "CmdElement.h"

int CmdElement::GetElementsType()
{
  return elementType;
}


void CmdElement::SetElementsType(int type)
{
  elementType = type;
}

CmdElement::CmdElement()
{
  for(int i=0; i<this->SIZE; i++)
    data[i] = '\0';
}
CmdElement::CmdElement(char cmdElement[])
{
  CmdElement();

  int i=0; 
  while(cmdElement[i] != '\0')
  {
    data[i] = cmdElement[i];
    i++;
  }
  for(; i<this->SIZE; i++)
    data[i] = '\0';
}

CmdElement CmdElement::operator = (CmdElement source)
{
  int i = 0;
  while(source.data[i] != '\0')
  {
    this->data[i] = source.data[i];
    i++;
  }
  for(; i<this->SIZE; i++)
    data[i] = '\0';

  elementType = source.elementType;

  return (*this);
}

bool CmdElement::operator == (CmdElement value)
{
  int i = 0;
  bool flag = true;
  while(value.data[i] != '\0' || data[i] != '\0')
  {
    if(value.data[i] != data[i])
    {
      flag = false;
    }
  }

  if(elementType != value.elementType)
  {
    flag = false;
  }

  return flag;
}