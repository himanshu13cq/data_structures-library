#ifndef REDIS_H
#define REDIS_H

#include <string>
#include "hash_map.h"
#include "dynamic_array.h"


class RedisLite
{
    public:
        RedisLite();
        void run();

    private:
        HashMap<std::string,std::string> store;
        std::string executeCommand(const std::string& line);
        DA<std::string> tokenize(const std::string& line);
        std::string handleSet(const DA<std::string>& tokens);
        std::string handleGet(const DA<std::string>& tokens);
        std::string handleDel(const DA<std::string>& tokens);
        std::string handleExists(const DA<std::string>& tokens);
        std::string handleCount();
        std::string handleClear();
};

#include "redis_lite.tpp"
#endif

