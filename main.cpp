#include "hash_map.h"
#include "dynamic_array.h"
#include <iostream>
#include "redis_lite.h"
using namespace std;

class abc
{
public:
int x;
int y;
abc(int a,int b): x(a), y(b) {}
bool operator==(const abc &a) const
{
    return this->x == a.x;
}
};

struct abchasher
{
    size_t operator()(const abc &a) const
    {
        return a.x;
    }
    
};

struct point{
    int a;
    int b;
    point(int x,int y): a(x), b(y) {}

    bool operator==(const point &other) const
    {
        return this->a == other.a;
    }
};

int main()
{   

    RedisLite app;
    app.run();


}