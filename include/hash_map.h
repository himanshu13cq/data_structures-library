#ifndef HASH_MAP
#define HASH_MAP
#include "linked_list.h"
#include "dynamic_array.h"
#include <cstddef>
#include <cstring>
#include <cstdint>
#include <type_traits>
#include <string>

template<typename K>
struct DefaultHash
{
    size_t operator()(const K &key) const
    {
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
        else if constexpr(std::is_same<K,double>::value)
        {   
            static_assert(sizeof(double) == sizeof(uint64_t),"Doing hashing of double will create trouble");
            uint64_t bits;
            std::memcpy(&bits,&key,sizeof(double));
            if constexpr(sizeof(size_t) < sizeof(uint64_t))
            {
                return static_cast<size_t>(bits ^ (bits >> 32));
            }
            else
            {
            return static_cast<size_t>(bits);
            }
        }
        else
        {   
            static_assert(requires(K a,K b) {{a==b} -> std::convertible_to<bool>;},"the user defined object should have a == operator overload");
            return reinterpret_cast<size_t>(&key);
        }
    }
};

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

template<typename K,typename V,typename H = DefaultHash<K>>
class HashMap
{
    private:
        int m_size;
        int m_capacity;
        DA<LinkedList<KV<K,V>>> buckets;
        H hasher; 
        
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
        void clear();

};

#include "hash_map.tpp"
#endif