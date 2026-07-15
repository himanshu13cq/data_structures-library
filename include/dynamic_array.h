#ifndef DA_H
#define DA_H

template <typename T>
class DA
{
    private:
        T *data;
        int m_size;
        int _capacity;
        void grow();
    public:
        DA();                              
        ~DA();                            
        DA(const DA &other);    
        DA& operator=(const DA &other);

        void append(const T &value);       
        void insert(int index, const T &value);
        void remove(int index);
        const T& get(int index) const;

        T& operator[](int index);
        const T& operator[](int index) const;

        int size() const;
        int capacity() const;
        bool isEmpty() const;
                     
};
#include "dynamic_arr.tpp"
#endif