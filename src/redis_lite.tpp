#include "redis_lite.h"
#include <iostream>
using namespace std;

RedisLite::RedisLite(){}

void RedisLite::run()
{
    while(true)
    {
        cout << "Enter the command:\n>";
        string line;

        if(!getline(cin,line))
        {
            break;
        }

        if(line == "EXIT")
        {
            break;
        }
        string result = executeCommand(line);
        cout << result <<"\n";
    }
}

string RedisLite::executeCommand(const string &line)
{
    DA<string> tokens = tokenize(line);
    if(tokens.isEmpty())
    {
        return "(error) Wrong Command";
    }

    string command = tokens[0];

    if(command == "SET")
    {   
        return handleSet(tokens);
    }
    else if(command == "GET")
    {
        return handleGet(tokens);
    }
    else if(command == "DEL")
    {
        return handleDel(tokens);
    }
    else if(command == "EXISTS")
    {
        return handleExists(tokens);
    }
    else if(command == "COUNT")
    {
        return handleCount();
    }
    else if(command == "CLEAR")
    {
        return handleClear();
    }   

    return "(error) Wrong Command";
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
    if(tokens.size() != 3)
    {
        return "(error) Wrong number of arguments for set";
    }
    store.insert(tokens[1],tokens[2]);
    return "Ok";
}

string RedisLite::handleGet(const DA<string> &tokens)
{
    if(tokens.size() != 2)
    {
        return "(error) Wrong number of arguments for GET";
    }
    if(store.contains(tokens[1]))
    {
        return store.get(tokens[1]);
    }
    else
    {
        return "Nill";
    }
    
}

string RedisLite::handleDel(const DA<string> &tokens)
{
    if(tokens.size() != 2)
    {
        return "(error) Wrong number of arguments for DEL";
    }
    if(store.remove(tokens[1]))
    {
        return "1";
    }
    return "0";
}

string RedisLite::handleExists(const DA<string> &tokens)
{
    if(tokens.size() != 2)
    {
        return "(error) Wrong number of arguments for EXISTS";
    }
    if(store.contains(tokens[1]))
    {
        return "1";
    }
    return "0";
}

string RedisLite::handleCount()
{
    return  to_string(store.size());
}

string RedisLite::handleClear()
{
    store.clear();
    return "Ok";
}