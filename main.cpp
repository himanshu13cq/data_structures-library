#include "hash_map.h"
#include "dynamic_array.h"
#include <iostream>
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
    point bita(10,34);

    HashMap<point,int> hm2;
    //HashMap<ad,ad,gemr.jwr
    hm2.insert(bita,26);
    cout << hm2.get(bita) <<endl;
    /*HashMap<abc,int,abchasher> hm1;
    abc alpha(10,20);
    hm1.insert(alpha,899);
    HashMap<int,int> hm;
    cout << "created hash map ";

    for(int i = 0;i < 8; ++i)
    {
        hm.insert(i,i*10);
    }
    cout << hm.get(3) <<endl; */
    return 0;
}