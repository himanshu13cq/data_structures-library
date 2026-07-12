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

template<typename K, typename V>
HashMap<K,V>::HashMap(const HashMap<K,V>& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    buckets = static_cast<LinkedList<KV<K,V>>*>(std::malloc(sizeof(LinkedList<KV<K,V>>) * m_capacity));
    for(int i = 0; i < m_capacity; ++i)
    {
        new (&buckets[i]) LinkedList<KV<K,V>>(other.buckets[i]);
    }
}

template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(const HashMap<K,V>& other)
{
    if(this == &other)
    {
        return *this;
    }

    for(int i = 0; i < m_capacity; ++i)
    {
        buckets[i].~LinkedList<KV<K,V>>();
    }
    std::free(buckets);

    m_size = other.m_size;
    m_capacity = other.m_capacity;
    buckets = static_cast<LinkedList<KV<K,V>>*>(std::malloc(sizeof(LinkedList<KV<K,V>>) * m_capacity));
    for(int i = 0; i < m_capacity; ++i)
    {
        new (&buckets[i]) LinkedList<KV<K,V>>(other.buckets[i]);
    }

    return *this;
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
V* HashMap<K,V>::find(const K &key)
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

    buckets[index].insertBack(element);
    m_size++;

    float loadFactor = static_cast<float>(m_size) / m_capacity;
    if(loadFactor > 0.9f)
    {
    rehash();
    }
}

template<typename K,typename V>
void HashMap<K,V>::rehash()
{
    int new_capacity = m_capacity * 2;

    LinkedList<KV<K,V>>* newBuckets = static_cast<LinkedList<KV<K,V>>*>(std::malloc(sizeof(LinkedList<KV<K,V>>) * new_capacity));

    for(int i = 0;i < new_capacity; ++i)
    {
        new (&newBuckets[i]) LinkedList<KV<K,V>>();
    }

    for(int i = 0;i < m_capacity; ++i)
    {
        for(auto &kv: buckets[i])
        {
            size_t index = hash(kv.key) % new_capacity;
            newBuckets[index].insertBack(kv);
        }
        buckets[i].~LinkedList<KV<K,V>>();
    }
    std::free(buckets);

    buckets = newBuckets;
    m_capacity = new_capacity;
}

template<typename K,typename V>
V& HashMap<K,V>::get(const K &key)
{
    V* found = find(key);
    if(found == nullptr)
    {
        insert(key,V());
        return *find(key);
    }
    return *found;
}

template<typename K,typename V>
bool HashMap<K,V>::contains(const K &key)
{
    return find(key) != nullptr;
}

template<typename K, typename V>
bool HashMap<K,V>::remove(const K &key)
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

template<typename K,typename V>
int HashMap<K,V>::size() const
{
    return m_size;
}

template<typename K,typename V>
bool HashMap<K,V>::isEmpty() const
{
    return m_size == 0;
}