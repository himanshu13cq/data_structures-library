#ifndef HASH_MAP
#define HASH_MAP

#include "linked_list.h"
#include <cstddef>

template<typename K,typename V>
struct KV
{
    K key;
    V value;   

    KV(K k, V v): key(k), value(v) {}
    bool operator==(const KV<K,V>& other) const
    {
        return key == other.key;
    }
};

template<typename K,typename V>
class HashMap
{
    private:
        int m_size;
        int m_capacity;
        LinkedList<KV<K,V>>* buckets;
        
        size_t hash(const K &key) const;

    public:
        HashMap();
        ~HashMap();
        void insert(const K &key,const V &value);


};

#include "hash_map.tpp"
#endif