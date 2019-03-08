#pragma once 
#include <iostream>

template <typename T>
class MyList
{
public:
  MyList();
	void InitList();      //用于初始化迭代器，使得能够从第一项开始遍历
	bool AddNode(T node);
	bool DelNode(T node);
	T* GetNextNode();
  T* GetCurNode();
  T* GetPreNode();
	bool SortNode();
  bool Empty();
  MyList<T> operator = (MyList<T> value);
  bool operator ==(MyList<T> value);

private:
  struct ListNode
  {
    T node;
    ListNode* link;
  };

private:
	ListNode* listHead;
  ListNode* listEnd;
	ListNode* iterator;
};

template<typename T>
MyList<T>::MyList()
{
  listHead = NULL;
  listEnd = NULL;
  iterator = NULL;
}

//用于初始化迭代器，使得能够从第一项开始遍历
template<typename T>
void MyList<T>::InitList()
{
  iterator = listHead;
}

//添加结点
template<typename T>
bool MyList<T>::AddNode(T node)
{
  ListNode* newNode = new ListNode();
  newNode->node = node;
  newNode->link = NULL;

  if(listHead == NULL)
  {
    listHead = newNode;
    listEnd = newNode;
    iterator = listHead;
  }
  else
  {
    listEnd->link = newNode;
    listEnd = newNode;
  }
  
	return true;
}

//删除结点
template<typename T>
bool MyList<T>::DelNode(T node)
{
  bool flag = false;
  ListNode* delNode = NULL;

  
  if(listHead->node == node)
  {
    delNode = listHead;
    listHead = listHead->link;
    flag = true;
    delete delNode;
    delNode = NULL;
  }
  else
  {
    iterator = listHead;
    delNode = listHead->link;
    while(delNode != NULL)
    {
      if(delNode->node == node)
      {
        iterator->link = delNode->link;
        flag = true;
        delete delNode;
        delNode = NULL;
        break;
      }
      else
      {
        iterator = delNode;
        delNode = delNode->link;
      }
    }
  }
  return flag;
}

template<typename T>
T* MyList<T>::GetNextNode()
{
  if(iterator != NULL)
      iterator = iterator->link;

  return &(iterator->node);
}

template<typename T>
T* MyList<T>::GetCurNode()
{
  return &(iterator->node);
}

template<typename T>
T* MyList<T>::GetPreNode()
{
  ListNode* preNode = listHead;
  ListNode* curNode = preNode->link;
  if(preNode->node == iterator->node)
  {
    std::cout << "这是第一个结点！" << std::endl;
    preNode = NULL;
  }
  else
  {

    while(curNode != NULL)
    {
      if(iterator->node == curNode->node)
      {
        break;
      }
      else
      {
        preNode = curNode;
        curNode = curNode->link;
      }
    }
  }
  return preNode;
}

template<typename T>
bool MyList<T>::SortNode()
{
  return false;
}

template<typename T>
bool MyList<T>::Empty()
{
  iterator = listHead;
  while(listHead != NULL)
  {
    iterator = listHead->link;
    delete listHead;
    listHead = iterator;
  }

  listHead = NULL;
  listEnd =NULL;
  iterator = NULL;

  return true;
}

template<typename T>
MyList<T> MyList<T>::operator =(MyList<T> value)
{
  return value;
}

template<typename T>
bool MyList<T>::operator ==(MyList<T> value)
{
  return false;
}