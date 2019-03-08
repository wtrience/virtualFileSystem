
#include "MyString.h"

MyString::MyString()
{
  for(int i=0; i<this->SIZE; i++)
    data[i] = '\0';
}

MyString::MyString(char str[])
{
  MyString();

  int i=0; 
  while(str[i] != '\0')
  {
    data[i] = str[i];
    i++;
  }
  for(; i<this->SIZE; i++)
    data[i] = '\0';
}

bool MyString::Compare(MyString value)
{
  bool result = true; //记录比较结果
  int i = 0;

  while(value.data[i] != '\0')
  {
    if(data[i] != value.data[i])
      result = false;
  }

  return result;
}

MyString MyString::operator = (MyString source)
{
  int i = 0;
  while(source.data[i] != '\0')
  {
    this->data[i] = source.data[i];
    i++;
  }
  for(; i<this->SIZE; i++)
    data[i] = '\0';

  return (*this);
}

bool MyString::operator ==(MyString value)
{
  int i = 0;
  bool flag = true;
  while(value.data[i] != '\0' || data[i] != '\0')
  {
    if(value.data[i] != data[i])
    {
      flag = false;
      break;
    }
    i++;
  }
  return flag;
}