//
// Created by xie on 2021/7/26.
//

#include <iostream>
#include "hash_table.h"
using namespace std;


DirectAddressTable::DirectAddressTable(): kTableSize_(10)
{
    for (int ii=0;ii <10;ii++)
        node_[ii]= nullptr;
}


DirectAddressTable::DirectAddressTable(int len): kTableSize_(len)
{
    for (int ii=0;ii <10;ii++)
        node_[ii]= nullptr;
}

DirectAddressTable::~DirectAddressTable()
{}

void DirectAddressTable::Insert(Node *n)
{
    node_[n->key] = n;
}

void DirectAddressTable::Delete(Node n)
{
    node_[n.key] = nullptr;
}


// int main()
// {
//     Node n1, n2;
//     n1.key = 2;
//     n1.value = 's';
//
//     n2.key = 3;
//     n2.value = 'a';
//
//     Node *pn=&n1, *pn2=&n2;
//
//     DirectAddressTable dat1;
//
//     dat1.Insert(pn);
//     dat1
//
//     cout<<dat1.node_[2]->value<<endl;
//     return 0;
// }