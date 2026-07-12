#include "hash_map.h"
#include <iostream>
using namespace std;

int main()
{
    HashMap<int,int> hm;
    cout << "created hash map ";

    for(int i = 0;i < 8; ++i)
    {
        hm.insert(i,i*10);
    }
    return 0;
}