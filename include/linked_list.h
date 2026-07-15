#ifndef LL_H
#define LL_H

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
        int m_size;

        Node<T>* createNode(const T &value);
        void destroyNode(Node<T>* node);
    
    public:

        class Iterator
        {
            private:
                Node<T>* current;

            public:
                Iterator(Node<T>* node): current(node) {}

                T& operator*()
                {
                    return current->data;
                }

                Iterator& operator++()
                {
                    current = current->next;
                    return *this;
                }

                bool operator!=(const Iterator& other) const
                {
                    return current != other.current;
                }
            };
        
        Iterator begin() const;
        Iterator end() const;

        LinkedList();
        ~LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);

        void insertFront(const T &value);
        void insertBack(const T &value);
        void deleteFront();
        T* find(const T &value) const;
        void insert(int index,const T &value);
        bool deleteValue(const T& value);
        void deleteAt(int index);
        void print() const;
        int size() const;
        void clear();
};

#include "linked_list.tpp"
#endif