#include "linked_list.h"
#include <iostream>

template<typename T>
Node<T>* LinkedList<T>::createNode(const T& value)
{
    Node<T>* node = static_cast<Node<T>*>(std::malloc(sizeof(Node<T>)));
    new (node) Node<T>(value);
    return node;
}


template<typename T>
void LinkedList<T>::destroyNode(Node<T>* node)
{
    node->~Node<T>();
    free(node);
}


template<typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}


template<typename T>
LinkedList<T>::~LinkedList()
{
    while(head != nullptr){
        Node<T>* node = head;
        head = head->next;
        destroyNode(node);
    }
    tail = nullptr;
}


template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if(this == &other){
        return *this;
    }   

    while(head != nullptr)
    {
       Node<T>* temp = head;
       head = head -> next;
       destroyNode(temp);
    }
    tail = nullptr;
    m_size = 0;

    Node<T>* node = other.head;
    while(node != nullptr)
    {
        insertBack(node->data);
        node = node->next;
    }
    return *this;
}


template<typename T>
void LinkedList<T>::insertFront(const T &value)
{
    Node<T>* newNode = createNode(value);
    newNode->next = head;
    head = newNode;
        if(tail == nullptr)
        {
            tail = newNode;
        }
    m_size++;
}


template<typename T>
void LinkedList<T>::insertBack(const T &value)
{
    Node<T>* newNode = createNode(value);
    newNode->next = nullptr;
    if(tail == nullptr)
    {
        tail = newNode;
         head = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
        m_size++;
}


template<typename T>
void LinkedList<T>::deleteFront()
{
    if(head == nullptr)
    {
       std::cerr << "underflow";
       exit(1);
    }
           
    if(head->next == nullptr)
    {
        tail = nullptr;
    }

    Node<T>* temp = head;
    head = head -> next;
    destroyNode(temp);
    m_size--;
}

template<typename T>
T* LinkedList<T>::find(const T &value) const
{
    Node<T>* node= head;
    while(node != nullptr)
    {
        if(node->data == value){
            return &node->data;
        }

        node = node->next;
    }
    return nullptr;
}


template<typename T>
void LinkedList<T>::insert(int index,const T &value)
{
    if(index > m_size)
    {
        std::cerr << "Out of index";
    }

    if(index == 0)
    {
        insertFront(value);
        return;
    }

    if(index == m_size)
    {
        insertBack(value);
        return;
    }

    Node<T>* prev = head;
    for(int i = 0;i < index - 1; ++i)
    {
        prev = prev->next;          
    }

    Node<T>* node = createNode(value);
    node->next = prev->next;
    prev->next = node;
    m_size++;
}


template<typename T>
void LinkedList<T>::print() const
{
    Node<T>* node = head;
    while(node != nullptr)
    {
        std::cout << node->data << std::endl;
        node = node->next;
    }
}


template<typename T>
void LinkedList<T>::deleteAt(int index)
{
    if(index >= m_size || index < 0)
    {
        std::cerr<<"out of index";
        exit(0);
    }

    if(index == 0)
    {
        deleteFront();
        return;
    }

    Node<T>* prev = head;
    for(int i = 0;i < index - 1; ++i)
    {
        prev = prev->next;
    }
    Node<T>* temp = prev->next;
    prev->next = prev->next->next;
    temp->next = nullptr;
    if(index == m_size - 1)
    {
        tail = prev;
    }
        destroyNode(temp);
        m_size--;
}


template<typename T>
const int LinkedList<T>::size() const
{
    return m_size;
}


