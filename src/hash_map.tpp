#include "hash_map.h"
#include "linked_list.h"
#include <cstdlib>
#include <new>
#include <type_traits>
#include <cstddef>
#include <string>

template<typename K,typename V>
HashMap<K,V>::HashMap()
{
    m_size = 0;
    m_capacity = 8;
    
    buckets = static_cast<LinkedList<KV<K,V>>*>(std::malloc(sizeof(LinkedList<KV<K,V>>) * m_capacity));
    
    for(int i = 0;i < m_capacity; ++i)
    {   
        new (&buckets[i]) LinkedList<KV<K,V>>();
    }
}

template<typename K,typename V>
HashMap<K,V>::~HashMap()
{
    for(int i = 0;i < m_capacity; ++i)
    {
        buckets[i].~LinkedList<KV<K,V>>();
    }
    free(buckets);
}

template<typename K,typename V>
size_t HashMap<K,V>::hash(const K &key) const{
    if constexpr(std::is_integral<K>::value)
    {
        return static_cast<size_t>(key);
    }
    else if constexpr(std::is_same<K,std::string>::value)
    {
        size_t h = 0;
        for(char c:key)
        {
            h = h * 31 + static_cast<unsigned char>(c);
        }
        return h;
    }
    else
    {
        static_assert(std::is_integral<K>::value || std::is_same<K,std::string>::value, "give only int and string");
    }
};

template<typename K,typename V>
void HashMap<K,V>::insert(const K &key,const V &value)
{
    size_t index = hash(key) % m_capacity;

    KV<K,V> element(key,value);
    KV<K,V>* existing = buckets[index].find(element);

    if(existing != nullptr)
    {
        existing->value = value;
        return;
    }

    buckets[index].insertBack(target);
    m_size++;
}