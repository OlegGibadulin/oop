//
//  list.cpp
//  lab_02
//
//  Created by Mac-HOME on 08/04/2019.
//  Copyright © 2019 Mac-HOME. All rights reserved.
//

#ifndef list_hpp
#define list_hpp

#include "list.h"

// BaseList

BaseList::BaseList() : sizeList(0) {}

BaseList::~BaseList()
{
    this->sizeList = 0;
}

size_t BaseList::size() const
{
    return sizeList;
}

// List: public methods

template <typename typeData>
List<typeData>::List() : head(nullptr), tail(nullptr) {}

template <typename typeData>
List<typeData>::List(const size_t countNodes, ...) : head(nullptr), tail(nullptr)
{
    va_list vlist;
    va_start(vlist, countNodes);
    
    typeData tmp;
    
    for (size_t i = 0; i < countNodes; ++i)
    {
        tmp = va_arg(vlist, typeData);
        this->append(tmp);
    }
    
    va_end(vlist);
}

template <typename typeData>
List<typeData>::List(const List<typeData>& someList) : head(nullptr), tail(nullptr)
{
    this->extend(someList);
}

template <typename typeData>
List<typeData>::List(List<typeData>&& someList)
{
    this->sizeList = someList->sizeList;
    this->head.reset(someList->head);
    this->tail.reset(someList->tail);
    
    someList->sizeList = 0;
    someList->head = nullptr;
    someList->tail = nullptr;
}

template <typename typeData>
List<typeData>::List(const typeData& data, const size_t countData) : head(nullptr), tail(nullptr)
{
    if (countData == 0)
        return;
    
    for (size_t i = 1; i < countData; ++i)
        this->append(data);
}

template <typename typeData>
List<typeData>::List(const std::initializer_list<typeData>& someList) : head(nullptr), tail(nullptr)
{
    for (const auto& data : someList)
        append(data);
}

template <typename typeData>
List<typeData>::~List() {}

template <typename typeData>
List<typeData>& List<typeData>::operator=(const List& someList)
{
    if (this != &someList)
    {
        this->clear();
        this->extend(someList);
    }
    
    return *this;
}

template <typename typeData>
List<typeData>& List<typeData>::operator=(List&& someList)
{
    if (this != someList)
    {
        this->clear();
        this->sizeList = someList->sizeList;
        this->head = someList->head;
        this->tail = someList->tail;
        
        someList->sizeList = 0;
        someList->head = nullptr;
        someList->tail = nullptr;
    }
    
    return *this;
}

template <typename typeData>
List<typeData>& List<typeData>::append(const typeData& data)
{
    std::shared_ptr <ListNode<typeData>> newNode = initNode(data);
    
    if (this->isEmpty())
        this->head = newNode;
    else
        this->tail->setNext(newNode);
    this->tail = newNode;
    
    return *this;
}

template <typename typeData>
List<typeData>& List<typeData>::operator+=(const typeData& data)
{
    this->append(data);
    return *this;
}

template <typename typeData>
List<typeData>& operator+(const List<typeData>& list, const typeData& data)
{
    List<typeData> newList(list);
    newList.append(data);
    return newList;
}

template <typename typeData>
List<typeData>& operator+(const typeData& data, const List<typeData>& list)
{
    List<typeData> newList(list);
    newList.insert(data);
    return newList;
}

template <typename typeData>
void List<typeData>::insert(const typeData& data, int posToAdd)
{
    if (posToAdd < 0)
        posToAdd = int (sizeList) + posToAdd;
    
    if (this->isEmpty() || posToAdd <= 0)
    {
        ListNode<typeData>* headNode = this->head;
        this->head = initNode(data, headNode);
    }
    else
    {
        ListNode<typeData> *cur = this->head;
        for (int i = 1; cur->getNext() && i < posToAdd; i++, cur = cur->getNext());
        ListNode<typeData>* nextNode = cur->getNext();
        ListNode<typeData>* newNode = initNode(data, nextNode);
        cur->setNext(newNode);
        if (nextNode == nullptr)
            this->tail = newNode;
    }
}

template <typename typeData>
void List<typeData>::extend(const List& ListToAdd)
{
    if (ListToAdd.isEmpty())
        return;
    
    if (this == &ListToAdd)
    {
        List<typeData> ListCopy;
        ListCopy = ListToAdd;
        addList(ListCopy);
    }
    else
    {
        addList(ListToAdd);
    }
}

template <typename typeData>
typeData& List<typeData>::remove(const typeData& dataToSearch)
{
    /*if (this->isEmpty())
     throw EmptyError();
     
     ListNode<typeData>* cur = this->head;
     ListNode<typeData>* tmp = this->head;
     
     for (; cur && cur->getData() != dataToSearch; tmp = cur, cur = cur->getNext());
     
     if (cur == nullptr)
     throw ValueError();
     
     deleteNode(cur, tmp);*/
}

template <typename typeData>
typeData& List<typeData>::pop()
{
    int posToDel = -1;
    if (this->isEmpty())
     throw EmptyError();
     
     if (std::abs(posToDel) >= int (sizeList))
     throw RangeError();
     
     ListNode<typeData>* cur = this->head;
     ListNode<typeData>* tmp = this->head;
     typeData retData;
     
     if (posToDel < 0)
     posToDel = int (sizeList) + posToDel;
     
     for (int i = 0; i != posToDel; tmp = cur, cur = cur->getNext(), ++i);
     retData = cur->getData();
     
     deleteNode(cur, tmp);
     
     return retData;
}

template <typename typeData>
void List<typeData>::clear()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->sizeList = 0;
}

template <typename typeData>
List<typeData>& List<typeData>::operator+=(const List& someList)
{
    this->extend(someList);
    return *this;
}

template <typename typeData>
bool List<typeData>::operator==(const List& someList) const
{
    return isNodesEqual(someList);
}

template <typename typeData>
bool List<typeData>::operator!=(const List& someList) const
{
    return !isNodesEqual(someList);
}

template <typename typeData>
ListIter<typeData> List<typeData>::begin()
{
    return ListIter<typeData>(head);
}

template <typename typeData>
ListIter<typeData> List<typeData>::end()
{
    return ListIter<typeData>(tail->getNext());
}

template <typename typeData>
ConstListIter<typeData> List<typeData>::begin() const
{
    return ConstListIter<typeData>(head);
}

template <typename typeData>
ConstListIter<typeData> List<typeData>::end() const
{
    return ConstListIter<typeData>(tail->getNext());
}

// List: protected methods

template <typename typeData>
std::shared_ptr<ListNode<typeData>> List<typeData>::initNode(const typeData& data, std::shared_ptr<ListNode<typeData>> ptrNode)
{
    std::shared_ptr<ListNode<typeData>> newNode;
    newNode = std::make_shared<ListNode<typeData>>();
    if (!newNode)
    {
        throw MemoryError(": method - initNode()");
    }
    newNode->setData(data);
    newNode->setNext(ptrNode);
    this->sizeList += 1;
    
    return newNode;
}

template <typename typeData>
void List<typeData>::deleteNode(ListNode<typeData> *cur, ListNode<typeData> *tmp)
{
    if (cur == this->head)
    {
        this->head = cur->getNext();
        delete(cur);
    }
    else
    {
        tmp->setNext(cur->getNext());
        delete(cur);
    }
    this->sizeList -= 1;
}

template <typename typeData>
void List<typeData>::addList(const List& ListToAdd)
{
    typeData data = ListToAdd.head->getData();
    std::shared_ptr<ListNode<typeData>> nextNode = ListToAdd.head->getNext();
    std::shared_ptr<ListNode<typeData>> nodeToAdd = initNode(data, nextNode);
    std::shared_ptr<ListNode<typeData>> cur = this->head;
    
    if (this->isEmpty())
    {
        cur = nodeToAdd;
        this->head = cur;
    }
    else
    {
        for (; cur->getNext(); cur = cur->getNext());
        cur->setNext(nodeToAdd);
        cur = cur->getNext();
    }
    
    std::shared_ptr<ListNode<typeData>> curToAdd = nextNode;
    
    for (; curToAdd; curToAdd = curToAdd->getNext(), cur = cur->getNext())
    {
        data = curToAdd->getData();
        nextNode = curToAdd->getNext();
        nodeToAdd = initNode(data, nextNode);
        cur->setNext(nodeToAdd);
    }
    this->tail = nodeToAdd;
}

template <typename typeData>
bool List<typeData>::isNodesEqual(const List<typeData>& someList) const
{
    std::shared_ptr<ListNode<typeData>> curL = this->head;
    std::shared_ptr<ListNode<typeData>> curR = someList.head;
    for (; curL && curR && curL->getData() == curR->getData(); )
    {
        curL = curL->getNext();
        curR = curR->getNext();
    }
    
    return (curL == nullptr && curR == nullptr) ? true : false;
}

template <typename typeData>
bool List<typeData>::isEmpty() const
{
    return (this->head == nullptr) ? true : false;
}

template <typename typeData> std::ostream& operator<<(std::ostream& stream, List<typeData>& list)
{
    stream << "List";
    ListIter<typeData> iter = list.begin();
    if (!iter.checkRange())
    {
        stream << " is empty";
    }
    else
    {
        stream << ":";
        for (; iter.checkRange(); iter.next())
            stream << " " << iter.getCur();
    }
    
 return stream;
}

#endif /* list_hpp */
