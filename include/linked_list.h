#ifndef LL_H
#define LL_H

#include <iostream>
#include <stdexcept>

template<typename T>
struct Node
{
    T data;
    Node* next;

    Node(const T &data) : data(data), next(nullptr) {};
};

template<typename T>
class LinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int _size;

        Node<T>* createNode(const T &value);
        void destroyNode(Node<T>* node);
    
    public:

        LinkedList();
        ~LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);

        void insertFront(const T &value);
        void insertBack(const T &value);
        void deleteFront();
        void search(const T &value);
        void insert(int index,const T &value);

       
};

#endif