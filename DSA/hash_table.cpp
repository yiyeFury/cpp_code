//
// Created by xie on 2021/7/26.
//

#include <iostream>
#include "hash_table.h"
using namespace std;


HashTable::HashTable(): kHashSize_(10)
{
    for (int ii=0;ii <kHashSize_;ii++)
        node_[ii]= nullptr;
}


HashTable::HashTable(int len): kHashSize_(len)
{
    for (int ii=0;ii <10;ii++)
        node_[ii]= nullptr;
}

HashTable::~HashTable()
{}


// int main()
// {
//     HashTable hs1;
//     cout<<hs1.kHashSize_<<endl;
//     return 0;
// }