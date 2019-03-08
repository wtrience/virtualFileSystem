#pragma once 

class MyString
{
public:
  const static int SIZE = 100;
  char data[SIZE];
  
public:
  MyString();
  MyString(char str[]);
  MyString operator = (MyString value);
  bool  operator == (MyString value);
  bool Compare(MyString value);
};