#include "linked_list.h"

template<typename T>
Node<T>* LinkedList<T>::createNode(const T& value)
{
    Node<T>* node = static_cast<Node<T>*>(std::malloc(sizeof(Node<T)));
    new (node) Node<T>();
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
    _size = 0;
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
    if(this == &other)
    {
        return *this;
    }

    ~LinkedList();
    _size = 0;

     Node<T>* temp = other.head;
     while(temp != nullptr)
     {
        Node<T>* node = createNode(temp->value);
        node->next = nullptr;
        if(tail == nullptr)
        {
            
        }
     }

}