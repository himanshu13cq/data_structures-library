#include "hash_map.h"
#include "linked_list.h"
#include "dynamic_array.h"

template<typename K,typename V,typename H>
HashMap<K,V,H>::HashMap()
{
    m_size = 0;
    m_capacity = 8;
    
    for(int i = 0;i < m_capacity; ++i)
    {   
        buckets.append(LinkedList<KV<K,V>>());
    }
}

template<typename K,typename V,typename H>
HashMap<K,V,H>::~HashMap()
{
}

template<typename K, typename V,typename H>
HashMap<K,V,H>::HashMap(const HashMap<K,V,H>& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    buckets = other.buckets;
}

template<typename K, typename V,typename H>
HashMap<K,V,H>& HashMap<K,V,H>::operator=(const HashMap<K,V,H>& other)
{   
    if(this == &other){
        return *this;
    }
    buckets = other.buckets;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    return *this;
}

template<typename K,typename V,typename H>
size_t HashMap<K,V,H>::hash(const K &key) const{
    return hasher(key);
}

template<typename K,typename V,typename H>
V* HashMap<K,V,H>::find(const K &key)
{
    size_t index = hash(key) % m_capacity;
    KV<K,V> target(key,V());

    KV<K,V>* existing = buckets[index].find(target);

    if(existing != nullptr)
    {
        return &(existing->value);
    }
    return nullptr;
}

template<typename K,typename V,typename H>
void HashMap<K,V,H>::insert(const K &key,const V &value)
{
    size_t index = hash(key) % m_capacity;

    KV<K,V> element(key,value);
    KV<K,V>* existing = buckets[index].find(element);

    if(existing != nullptr)
    {
        existing->value = value;
        return;
    }

    buckets[index].insertBack(element);
    m_size++;

    float loadFactor = static_cast<float>(m_size) / m_capacity;
    if(loadFactor > 0.9f)
    {
    rehash();
    }
}

template<typename K,typename V,typename H>
void HashMap<K,V,H>::rehash()
{
    int new_capacity = m_capacity * 2;

    DA<LinkedList<KV<K,V>>> newBuckets; 
    for(int i = 0;i < new_capacity; ++i)
    {
        newBuckets.append(LinkedList<KV<K,V>>());
    }

    for(int i = 0;i < m_capacity; ++i)
    {
        for(auto &kv: buckets[i])
        {
            size_t index = hash(kv.key) % new_capacity;
            newBuckets[index].insertBack(kv);
        }
    }

    buckets = newBuckets;
    m_capacity = new_capacity;
}

template<typename K,typename V,typename H>
V& HashMap<K,V,H>::get(const K &key)
{
    V* found = find(key);
    if(found == nullptr)
    {
        insert(key,V());
        return *find(key);
    }
    return *found;
}

template<typename K,typename V,typename H>
bool HashMap<K,V,H>::contains(const K &key)
{
    return find(key) != nullptr;
}

template<typename K, typename V,typename H>
bool HashMap<K,V,H>::remove(const K &key)
{
    size_t index = hash(key) % m_capacity;
    KV<K,V> target(key, V());
    bool removed = buckets[index].deleteValue(target);
    if(removed)
    {
        m_size--;
    }
    return removed;
}

template<typename K,typename V,typename H>
int HashMap<K,V,H>::size() const
{
    return m_size;
}

template<typename K,typename V,typename H>
bool HashMap<K,V,H>::isEmpty() const
{
    return m_size == 0;
}