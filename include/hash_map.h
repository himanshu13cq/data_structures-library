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
        V* find(const K &key);
        void rehash();

    public:
        HashMap();
        ~HashMap();
        HashMap(const HashMap& other);
        HashMap& operator=(const HashMap& other);
        void insert(const K &key,const V &value);
        V& get(const K &key);
        bool contains(const K& key);
        bool remove(const K& key);
        int size() const;
        bool isEmpty() const;

};

#include "hash_map.tpp"
#endif