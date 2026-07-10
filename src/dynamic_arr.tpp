#include "dynamic_array.h"
#include <iostream>

template<typename T>        //constructor
DA<T>::DA()
{
    m_size = 0;
    _capacity = 0;
    data = nullptr;
}


template<typename T>        //destructor
DA<T>::~DA()
{   
    for(int i = 0;i < m_size;i++)
    {
        data[i]. ~T();
    }
    std::free(data);
}


template<typename T>        //copy constructor
DA<T>::DA(const DA &other)
{
    m_size = other.m_size;
    _capacity = other._capacity;
    data = static_cast<T*>(std::malloc(_capacity * sizeof(T)));
        
    for(int i = 0;i < m_size; ++i)
    {   
        new (&data[i]) T();
        data[i] = other.data[i];
    }
}
 

template<typename T>        //assignment operator overload
DA<T>& DA<T>::operator=(const DA &other)
{   
    if(this == &other)
    {
        return *this;
    }

    for(int i = 0;i < m_size; ++i)
    {
        data[i].~T();
    }
    std::free(data);

    m_size = other.m_size;
    _capacity = other._capacity;
    data = static_cast<T*>(std::malloc(_capacity * sizeof(T)));
        
    for(int i = 0;i < m_size; ++i)
    {   
        new (&data[i]) T();
        data[i] = other.data[i];
    }

    return *this;
}


template<typename T>        //append
void DA<T>::append(const T &value)
{
    if(m_size == _capacity)
    {
        _capacity = _capacity * 2 + (_capacity? 0:1);
        T* ptr = static_cast<T*>(std::malloc(_capacity * sizeof(T)));

        for(int i = 0;i < m_size; ++i)
        {
            new (&ptr[i]) T();
            ptr[i] = data[i];
        }
            
        for(int i = 0;i < m_size; ++i)
        {    
            data[i].~T();
        }
        std::free(data);
        data = ptr;
           
    }

    data[m_size] = value;
    m_size++;
 }


template<typename T>              //[]operator overload
T& DA<T>::operator[](int index)
{
    if(index >= m_size || index < 0)
    {
        std::cerr << "Index out of Bounds" << "\n";
        exit(1);
    }
    else
    {
        return *(data + index);
    }
}


template<typename T>
void DA<T>::insert(int index,const T &value)
{
    if(index < 0 || index >= m_size)
    {
        std::cerr << "Out of bound";
        exit(0);
    }

    if(m_size == _capacity)
    {
        _capacity = _capacity * 2 + (_capacity? 0:1);
        T* ptr = static_cast<T*>(std::malloc(_capacity * sizeof(T)));

        for(int i = 0;i < m_size; ++i)
        {
            new (&ptr[i]) T();
            ptr[i] = data[i];
        }
            
        for(int i = 0;i < m_size; ++i)
        {    
            data[i].~T();
        }
        std::free(data);
        data = ptr;
    }

    for(int i = m_size;i > index; --i)
    {
        data[i] = data[i-1];
    }
    data[index] = value;
    m_size++;
}

template<typename T>
void DA<T>::remove(int index)
{
    if(index < 0 || index >= m_size)
    {
        std::cerr << "Index out of bounds";
        exit(0);
    }

    for(int i = index;i < m_size - 1; ++i){
        data[i] = data[i+1];
    }

    data[m_size - 1].~T();
    m_size--;
}

template<typename T>
const T& DA<T>::get(int index) const
{
    if(index < 0 || index >= m_size)
    {
        std::cerr << "Index out of bound";
        exit(0);
    }

    return data[index];
}

template<typename T>
int DA<T>::size() const
{
    return m_size;
}


template<typename T>
int DA<T>::capacity() const
{
    return _capacity;
}


template<typename T>
bool DA<T>::isEmpty() const
{
    return m_size == 0;
}
