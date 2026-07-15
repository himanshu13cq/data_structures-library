#include "redis_lite.h"
#include <iostream>
using namespace std;

RedisLite::RedisLite(){}

void RedisLite::run()
{
    while(true)
    {
        cout << "Enter the command:\n";
        string line;
        getline(cin,line);
        if(line == "EXIT")
        {
            break;
        }
        string result = RedisLite::executeCommand(line);
        cout << result <<"\n";
    }
}

string RedisLite::executeCommand(const string &line)
{
    DA<string> tokens = RedisLite::tokenize(line);
    if(tokens.isEmpty())
    {
        return "Wrong Command";
    }

    string command = tokens[0];

    if(command == "SET")
    {   
        return RedisLite::handleSet(tokens);
    }
    else if(command == "GET")
    {
        return RedisLite::handleGet(tokens);
    }
    else if(command == "DEL")
    {
        return RedisLite::handleDel(tokens);
    }
    else if(command == "Exists")
    {
        return RedisLite::handleExists(tokens);
    }
    else if(command == "Count")
    {
        return RedisLite::handleCount();
    }
    else if(command == "Clear")
    {
        return RedisLite::handleClear();
    }   

    return "Wrong Command";
}

DA<string> RedisLite::tokenize(const string &line)
{   
    DA<string> tokens;
    string current;
    for(auto &i:line)
    {   
        if(i != ' ')
        current += i;

        else
        {
            if(current != "")
            {
                tokens.append(current);
                current = "";
            }
        }
    }
    if(current != "")
    tokens.append(current);

    return tokens;
}

string RedisLite::handleSet(const DA<string> &tokens)
{
    return "Set";
}

string RedisLite::handleGet(const DA<string> &tokens)
{
    return "Get";
}

string RedisLite::handleDel(const DA<string> &tokens)
{
    return "Del";
}

string RedisLite::handleExists(const DA<string> &tokens)
{
    return "Exists";
}

string RedisLite::handleCount()
{
    return "count";
}

string RedisLite::handleClear()
{
    return "clear";
}